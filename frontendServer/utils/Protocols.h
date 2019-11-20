#pragma once

#include <algorithm>

#include "SocketHelper.h"

// This part shares variable from chatserver.cc. It is not very elegant.
extern int sock;
extern int server_index;
extern vector<string> forwarding_addrs;
extern vector<unsigned short> forwarding_ports;
extern vector<string> bind_addrs;
extern vector<unsigned short> bind_ports;
extern map<pair<string, unsigned short>, int> servers_mapping;
extern map<pair<string, unsigned short>, int> clients_mapping;
extern map<pair<string, unsigned short>, string> clients_name;

// An abstract interface for any type of Protocol.
// receive_from_client and receive_from_server functions are marked as pure virtual
// function so any protocol must implemented both of them
class AbstractProtocol {
public:
  virtual void receive_from_client(const pair<string, unsigned short>& p, const string& message) = 0;
  virtual void receive_from_server(const pair<string, unsigned short>& p, const string& message) = 0;
};

// unordered protocol implementation
class UnorderedProtocol : public AbstractProtocol {
public:
  // Any time it receives message from any other server, it must be a chat message.
  // As a result, it will automatically send it to its clients without queuing.
  void receive_from_server(const pair<string, unsigned short>& p, const string& message) override
  {
    int square = message.find("<");
    int room_num = stoi(message.substr(0, square));
    for (const auto& key_value : clients_mapping) {
      auto person = key_value.first;
      auto person_rn = key_value.second;
      if (person_rn == room_num)
        UDP_send(sock, person.first, person.second, message.substr(square, message.length() - square));
    }
  }
  // Any time it receives chat message from client, it will multicast it to all servers
  // listed in the serverListFile
  void receive_from_client(const pair<string, unsigned short>& p, const string& message) override
  {
    for (int i = 0; i < forwarding_addrs.size(); ++i)
      UDP_send(sock, forwarding_addrs[i], forwarding_ports[i], to_string(clients_mapping[p]) + "<" + clients_name[p] + "> " + message);    
  }
};

// fifo protocol implementation
// Each server has its own self_cnt as tick-tock count (initialized as 0), every time
// the server multicasts chat message to other server, it will increase the count and
// attched the count to the message. The recipient would know the order that the sender
// sends the message
// client-server message format:
//        chat_message_content
// server-server message format:
//        self_cnt#chatting_room_number<client_name> chat_message_content
class FIFOProtocol : public AbstractProtocol {
  int self_cnt = 0;
  // every server has its own message queue in this server
  std::map<pair<string, unsigned short>, int> others_cnt;
  std::map<pair<string, unsigned short>, vector<pair<int, string> > > others_queue;
public:
  // 1. Separate the self_cnt from the received message
  // 2. Add the self_cnt and other message info into the sending queue
  // 3. Check the message with the lowest self_cnt can be send from the sender server
  //    (no other message has a smaller self_cnt hasn't been received). If it cant be
  //    sent then quit. Message queue for other servers will not be updated
  // 4. Send the message with the lowest self_cnt
  // 5. Go to 3
  void receive_from_server(const pair<string, unsigned short>& p, const string& message) override
  {
    int sign = message.find("#");
    int recv_cnt = stoi(message.substr(0, sign));
    others_queue[p].push_back(make_pair(recv_cnt, message.substr(sign + 1, message.length() - sign - 1)));
    sort(others_queue[p].begin(), others_queue[p].end());
    debug("Queue info : %d %d\n", others_queue[p][0].first, others_cnt[p] + 1);
    while (!others_queue[p].empty() && others_queue[p][0].first == others_cnt[p] + 1) {
      ++others_cnt[p];
      string send_msg = others_queue[p][0].second;
      others_queue[p].erase(others_queue[p].begin());
      int square = send_msg.find("<");
      int room_num = stoi(send_msg.substr(0, square));
      for (const auto& key_value : clients_mapping) {
        auto person = key_value.first;
        auto person_rn = key_value.second;
        if (person_rn == room_num)
          UDP_send(sock, person.first, person.second, send_msg.substr(square, send_msg.length() - square));
      }
    }
  }
  // 1. increase self_cnt
  // 2. attach self_cnt to the message and multicast it to all the servers
  void receive_from_client(const pair<string, unsigned short>& p, const string& message) override
  {
    ++self_cnt;
    for (int i = 0; i < forwarding_addrs.size(); ++i) {
      string send_msg = to_string(self_cnt) + "#" + to_string(clients_mapping[p]) + "<" + clients_name[p] + "> " + message;
      UDP_send(sock, forwarding_addrs[i], forwarding_ports[i], send_msg);
    }
  }
};

// total protocol implementation
// id_num           : a unique marker for messages for each single server
// message_id       : a unique marker for messages for all servers. This is computed
//                    by id_num and server_index, so it will be different whatever
//                    where the message comes from. This is needed to avoid mistakes
//                    caused by two messaging having exactly the same contents.
// message_priority : sending order voted by all servers. This is computed by maximum
//                    proposed_num and server_index. It can naturally compare messages
//                    which have the same server_index. It is used as tie-breaker
// queue            : all messages' content, message_id, message_priority and ready-to-send
//                    status (bool)
// proposals        : record all voting results for every message which it call for a
//                    vote
// client-server message format:
//        chat_message_content
// server-server message format
//        # message_id $ room_num <client_name> chat_message_content
//        message_priority # message_id $ room_num <client_name> chat_message_content
//        @ message_priority # message_id $ room_num <client_name> chat_message_content
// There are totally 3 steps in server-server messaging. The first is call for voting.
// The second is responding to the voting. The third is inform all servers the voting
// results.
const int MAX_SERVER = 1000;
class TotalProtocol : public AbstractProtocol {
  int proposed_num = 0;
  int agreed_num = 0;
  int id_num = 0;
  std::vector<pair<pair<int,int>, pair<bool,string> > > queue;
  std::map<int, std::vector<int> > proposals;
public:
  // This will attach proposed num to the message and send it back to the server which
  // calls for voting
  //    recv format:      # message_id $ room_num <client_name> chat_message_content
  //    send format:      message_priority # message_id $ room_num <client_name> chat_message_content
  void receive_vote(const pair<string, unsigned short>& p, const string& message)
  {
    proposed_num = max(proposed_num, agreed_num) + 1;
    int message_priority = server_index + proposed_num * MAX_SERVER;
    int sign = message.find("#");
    int dollar = message.find("$");
    int message_id = stoi(message.substr(sign + 1, dollar - sign - 1));
    queue.push_back(make_pair(make_pair(message_priority, message_id), make_pair(false, message.substr(dollar + 1, message.length() - dollar - 1))));
    UDP_send(sock, p.first, p.second, to_string(message_priority) + message);
  }
  // This will collect the voting results. If the servers receive all voting results
  // for a message, it will decide the final sending ordering by picking the maximum
  // and inform all servers. Otherwise, it will temporarily store the partial voting
  // results in proposals.
  //    recv format:      message_priority # message_id $ room_num <client_name> chat_message_content
  //    send format:      @ message_priority # message_id $ room_num <client_name> chat_message_content
  void receive_collect(const pair<string, unsigned short>& p, const string& message)
  {
    int sign = message.find("#");
    int dollar = message.find("$");
    int square = message.find("<");
    int message_priority = stoi(message.substr(0, sign));
    int message_id = stoi(message.substr(sign + 1, dollar - sign - 1));
    proposals[message_id].push_back(message_priority);
    // Check whether all voting results have been collected
    if (proposals[message_id].size() == forwarding_addrs.size()) {
      // Choosing the maximum as final sending order
      sort(proposals[message_id].begin(), proposals[message_id].end());
      message_priority = proposals[message_id].back();
      for (int i = 0; i < forwarding_addrs.size(); ++i) {
        string send_msg = "@" + to_string(message_priority) + message.substr(sign, message.length() - sign);
        UDP_send(sock, forwarding_addrs[i], forwarding_ports[i], send_msg);
      }
      proposals.erase(message_id);
    }
  }
  // If the server receives a message starting with '@'. Then it shows that the message
  // is ready to send. If there isn't any potential messaging need be sent early (by checking
  // all proposed history. This would work since the final sending order will never smaller
  // than it proposed.)
  //    recv format:      @ message_priority # message_id $ room_num <client_name> chat_message_content
  //    send format:      <client_name> chat_message_content
  void receive_deliver(const pair<string, unsigned short>& p, const string& message)
  {
    int sign = message.find("#");
    int dollar = message.find("$");
    int square = message.find("<");
    int message_priority = stoi(message.substr(1, sign - 1));
    int message_id = stoi(message.substr(sign + 1, dollar - sign - 1));
    for (int i = 0; i < queue.size(); ++i)
      if (queue[i].first.second == message_id) {
        queue[i].first.first = message_priority;
        queue[i].second.first = true;
      }
    agreed_num = max(agreed_num, message_priority / MAX_SERVER);
    sort(queue.begin(), queue.end());
    // Keep sending when there are multiple ready-to-send messages
    while (!queue.empty() && queue[0].second.first) {
      string send_msg = queue[0].second.second;
      queue.erase(queue.begin());
      int square = send_msg.find("<");
      int room_num = stoi(send_msg.substr(0, square));
      for (const auto& key_value : clients_mapping) {
        auto person = key_value.first;
        auto person_rn = key_value.second;
        if (person_rn == room_num) {
          UDP_send(sock, person.first, person.second, send_msg.substr(square, send_msg.length() - square));
        }
      }
    }
  }
  // Decide what kind of message it received from servers and how to treat it by
  // analysing its format.
  void receive_from_server(const pair<string, unsigned short>& p, const string& message) override
  {
    if (message[0] == '#') receive_vote(p, message);
    else if (message[0] == '@') receive_deliver(p, message);
    else receive_collect(p, message);
  }
  // When receive a chat message from clients, the server will always call for a
  // vote first.
  //    recv format:      <client_name> chat_message_content
  //    send format:      # message_id $ room_num <client_name> chat_message_content
  void receive_from_client(const pair<string, unsigned short>& p, const string& message) override
  {
    ++id_num;
    int message_id = server_index + id_num * MAX_SERVER;
    for (int i = 0; i < forwarding_addrs.size(); ++i) {
      string send_msg = "#" + to_string(message_id) + "$" + to_string(clients_mapping[p]) + "<" + clients_name[p] + "> " + message;
      UDP_send(sock, forwarding_addrs[i], forwarding_ports[i], send_msg);
    }
  }
};

// causal protocol implementation
// V_queue          : the vector clock for this server
// message_queue    : queued messages and their vector clocks with sender info
// It should be noticed that when there is a message incoming with a new vector
// clock, we know that the
// client-server message format:
//        chat_message_content
// server-server message format:
//        V1#V2#V3#...#chatting_room_number<client_name> chat_message_content
class CausalProtocol : public AbstractProtocol {
  vector<int> V;
  vector<pair<vector<int>,int> > V_queue;
  vector<string> message_queue;
public:
  // This can attach a vector to message and return processed message
  string encode_V(const vector<int>& V_in, const string& message)
  {
    string msg = message;
    for (int i = forwarding_addrs.size() - 1; i >= 0; --i)
      msg = to_string(V_in[i]) + "#" + msg;
    return msg;
  }
  // This can extract the vector info from the message and return the original
  // message
  string decode_V(vector<int>& V_in, const string& message)
  {
    V_in.clear();
    string msg = message;
    for (int i = 0; i < forwarding_addrs.size(); ++i) {
      int sign = msg.find('#');
      V_in.push_back(stoi(msg.substr(0, sign)));
      msg = msg.substr(sign + 1, msg.length() - sign - 1);
    }
    return msg;
  }
  // If the server receives a message with a vector, it will always add it into
  // the message queue first. Then keep finding messages in queue that ready-to-send.
  // The principle is that, the queued message can only have 1 larger than server's
  // itself vector clock on sender's position. Other positions can not be larger than
  // its.
  void receive_from_server(const pair<string, unsigned short>& p, const string& message) override
  {
    V.resize(forwarding_addrs.size(), 0);
    vector<int> V_in;
    string send_msg = decode_V(V_in, message);
    V_queue.push_back(make_pair(V_in, servers_mapping[p]));
    message_queue.push_back(send_msg);
    bool flag;
    do {
      flag = false;
      for (int i = 0; i < V_queue.size(); ++i) {
        bool can_send = true;
        int sender = V_queue[i].second;
        for (int j = 0; j < V_queue[i].first.size(); ++j) {
          if (j != sender && V_queue[i].first[j] > V[j])
            can_send = false;
          if (j == sender && V_queue[i].first[j] != V[j] + 1)
            can_send = false;
        }
        if (sender == server_index)
          can_send = true;
        if (can_send) {
          flag = true;
          send_msg = message_queue[i];
          int square = send_msg.find("<");
          int room_num = stoi(send_msg.substr(0, square));
          for (const auto& key_value : clients_mapping) {
            auto person = key_value.first;
            auto person_rn = key_value.second;
            if (person_rn == room_num)
              UDP_send(sock, person.first, person.second, send_msg.substr(square, send_msg.length() - square));
          }
          for (int j = 0; j < V_queue[i].first.size(); ++j) {
            V[j] = max(V[j], V_queue[i].first[j]);
          }
          message_queue.erase(message_queue.begin() + i);
          V_queue.erase(V_queue.begin() + i);
          break;
        }
      }
    } while (flag);
  }
  // When receive a chat message from clients, the server will always attach
  // the vector clock to it and multicast it to all servers.
  //    recv format:      <client_name> chat_message_content
  //    send format:      V1#V2#V3#...#chatting_room_number<client_name> chat_message_content
  void receive_from_client(const pair<string, unsigned short>& p, const string& message) override
  {
    V.resize(forwarding_addrs.size(), 0);
    ++V[server_index];
    for (int i = 0; i < forwarding_addrs.size(); ++i) {
      string send_msg = encode_V(V, to_string(clients_mapping[p]) + "<" + clients_name[p] + "> " + message);
      UDP_send(sock, forwarding_addrs[i], forwarding_ports[i], send_msg);
    }
  }
};