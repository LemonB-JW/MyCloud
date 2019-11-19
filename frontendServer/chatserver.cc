#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <cctype>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <map> 
#include <memory>

#include "SocketHelper.h"
#include "Protocols.h"

using namespace std;

// server_index : index in the server list that is currently running
int sock;
int server_index;

vector<string> forwarding_addrs;
vector<unsigned short> forwarding_ports;
vector<string> bind_addrs;
vector<unsigned short> bind_ports;

// servers_mapping : mapping addr:port(server) to the server index
// clients_mapping : mapping addr:port(client) to the chatting room number
//                   it is set to 0 if the client is not in any chatting room
// clients_name : mapping addr:port(client) to the nick name
map<pair<string, unsigned short>, int> servers_mapping;
map<pair<string, unsigned short>, int> clients_mapping;
map<pair<string, unsigned short>, string> clients_name;

// Different protocols only differ when they deal with server-server message
// (call receive_from_server) and client-server chat message (call receive_from_client).
// If the server receives an client-server command, it is treated the same as
// the following
// It should be noticed that, some protocols need all listed servers working to
// make them work (like TotalProtocol, it will do nothing until it receive all
// voting results from all listed server)
shared_ptr<AbstractProtocol> protocol;

// Read all fowarding addresses, forwarding ports, bind addresses and bind ports
// from file whose name is filename
void load_forwarding_and_bind_info(string filename) {
  ifstream file(filename);
  string line;
  // Load files line by line
  while (getline(file, line)) {
    // Count the number of addresses and ports for each line by checking if there
    // is a ',' contained
    if (line.find(',') != std::string::npos) {
      // This branch will parse data line like : 127.0.0.1:5000,127.0.0.1:8000, no
      // extra space or empty new line are allowed in the server list
      int colon1 = line.find(':');
      int comma = line.find(',');
      int colon2 = line.rfind(':');
      string addr1 = line.substr(0, colon1);
      int port1 = stoi(line.substr(colon1 + 1, comma - colon1 - 1));
      string addr2 = line.substr(comma + 1, colon2 - comma - 1);
      int port2 = stoi(line.substr(colon2 + 1, line.length() - colon2 - 1));
      forwarding_addrs.push_back(addr1);
      forwarding_ports.push_back((unsigned short) port1);
      bind_addrs.push_back(addr2);
      bind_ports.push_back((unsigned short) port2);
      debug("%s %s %s %s\n",
        line.substr(0, colon1).c_str(),
        line.substr(colon1 + 1, comma - colon1 - 1).c_str(),
        line.substr(comma + 1, colon2 - comma - 1).c_str(),
        line.substr(colon2 + 1, line.length() - colon2 - 1).c_str()
      );
    } else {
      // This branch will parse data line like : 127.0.0.1:5000
      int colon = line.find(':');
      string addr1 = line.substr(0, colon);
      int port1 = stoi(line.substr(colon + 1, line.length() - colon - 1));
      string addr2 = addr1;
      int port2 = port2;
      forwarding_addrs.push_back(addr1);
      forwarding_ports.push_back((unsigned short) port1);
      bind_addrs.push_back(addr1);
      bind_ports.push_back((unsigned short) port1);
      debug("%s %s %s %s\n",
        line.substr(0, colon).c_str(),
        line.substr(colon + 1, line.length() - colon - 1).c_str()
      );
    }
  }
  for (int i = 0; i < forwarding_addrs.size(); ++i) {
    auto p = make_pair(forwarding_addrs[i], forwarding_ports[i]);
    servers_mapping[p] = i;
  }
  file.close();
}

void worker(string addr, unsigned short port, string message)
{
  debug("###### %s:%s [%s] %d\n", addr.c_str(), to_string(port).c_str(), message.c_str(), clients_mapping.size());

  auto p = make_pair(addr, port);
  // Query whether the incoming addr:port exists in the server list, since we only
  // use a fixed number of servers here.
  if (servers_mapping.find(p) != servers_mapping.end()) {
    // This branch deal with server-server messaging
    protocol->receive_from_server(p, message);
  }
  else {
    // This branch deal with client-server messaging
    // Check whether the message comes from new clients
    if (clients_mapping.find(p) == clients_mapping.end()) {
      // Add the client's nick name (default as addr:port) and chatting room status
      // (default as not in any chatting room)
      clients_mapping[p] = 0;
      clients_name[p] = addr + ":" + to_string(port);
    }

    if (message.length() >= 6 && message.substr(0, 6) == "/join ") {
      // Deal with join command. If the client is not currently in any chatting room,
      // then respond with OK.
      if (clients_mapping[p] > 0)
        UDP_send(sock, addr, port, "-ERR You have already in room " + to_string(clients_mapping[p]));
      else {
        int room_num = stoi(message.substr(6, message.length() - 6));
        clients_mapping[p] = room_num;
        UDP_send(sock, addr, port, "+OK You are now in " + std::to_string(room_num));
      }
    } else if (message == "/part") {
      // Deal with part command. If the client is current in a chatting room, then
      // respond with OK.
      if (!clients_mapping[p])
        UDP_send(sock, addr, port, "-ERR You are not in a room");
      else {
        clients_mapping[p] = 0;
        UDP_send(sock, addr, port, "+OK You have quited");
      }
    } else if (message.length() > 6 && message.substr(0, 6) == "/nick ") {
      // Deal with nick command. This command will always execute successfully with
      // correct format
      string new_name = message.substr(6, message.length() - 6);
      UDP_send(sock, addr, port, "+OK Your name is changed from " + clients_name[p] + " to " + new_name);
      clients_name[p] = new_name;
    } else if (message == "/quit") {
      // Deal with quit command. This will delete all the client info from server,
      // which are chatting room number and nick name
      clients_mapping.erase(p);
      clients_name.erase(p);
    } else if (message[0] == '/') {
      // If server receive a message from client which starts with '/', while it doesn't
      // match any of the above commands, this means it is a invalid message and do nothing
      // for it
      UDP_send(sock, addr, port, "-ERR Invalid operation");
    } else {
      // If the message doesn't start with '/', it can be treated as a chat message which
      // a client sends to his chatting room. When the client is not in any chatting room
      // then the server will response an error and do nothing for it. Otherwise, protocol
      // will take over it
      if (!clients_mapping[p]) {
        UDP_send(sock, addr, port, "-ERR You are not in a room");
      } else {
        protocol->receive_from_client(p, message);
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "*** Author: Xuan Wang  (xuanw)\n");
    exit(1);
  }

  // The last two commands must be server list and the index of current server in that list
  // Two command options are implemented here:
  // -o : switch between different protocols
  // -v : print debug info on server's screen
  char c;
  // If the user doesn't manually input the protocol name, the server will detect that case
  // and use default protocol (unordered)
  bool o_set = false;
  while ((c = getopt(argc, argv, "o:v")) != -1) {
    switch (c) {
      case 'o':
        if (!strcmp(optarg, "unordered"))
          protocol = make_shared<UnorderedProtocol>();
        else if (!strcmp(optarg, "fifo"))
          protocol = make_shared<FIFOProtocol>();
        else if (!strcmp(optarg, "causal"))
          protocol = make_shared<CausalProtocol>();
        else if (!strcmp(optarg, "total"))
          protocol = make_shared<TotalProtocol>();
        else {
          // If the input of protocol doesn't match any of the above, the server will trigger
          // error and terminate
          printf("Unknown ordering: '%s' (supported: unordered, fifo, total)\n", optarg);
          exit(1);
        }
        o_set = true;
        break;
      case 'v':
        verbose = true;
        break;
      default:
        fprintf(stderr, "Syntax: %s [-o protocolName] [-v] serverListFile indexInServerListFile\n", argv[0]);
        exit(1);
    }
  }
  if (!o_set) {
    protocol = make_shared<UnorderedProtocol>();
  }

  string filename = string(argv[argc - 2]);
  server_index = atoi(argv[argc - 1]) - 1;
  string bind_addr;
  int bind_port;

  // load files from serverListFile
  load_forwarding_and_bind_info(filename);
  
  // listen to the binding address and port
  bind_addr = bind_addrs[server_index];
  bind_port = bind_ports[server_index];

  // bind a name to a socket
  sock = socket_bind(bind_addr, bind_port);
  debug("Start listening to %s %d\n", bind_addr.c_str(), (int)bind_port);

  // THe server is implemented in single thread and only respond when there is a message coming
  while (true) {
    string addr;
    unsigned short port;
    string message = UDP_recv(sock, addr, port);
    worker(addr, port, message);
    // UDP_send(sock, addr, port, message);
  }
  return 0;
}  