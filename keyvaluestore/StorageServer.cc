// Author: Jiaying Guo

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 
#include <pthread.h>
#include <stdbool.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <typeinfo>
#include <limits.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <bits/stdc++.h> 
#include <ctime>
#include <sys/file.h>
#include "../lib/BigTable.h"
#include "../lib/Utility.h"

using namespace std; 

/*Self defined data structure for passing the file descriptors, directory name, v_flag, etc for each worker thread*/
typedef struct read_args{
  int fd;
  int v_flag;
  int index;
  
}read_args;


/* struct for storing IP address information */
typedef struct addr_info{
  string ip;
  int port;
}addr_info;

 /*Trim extra space from the start of the string s (in place)*/
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

 /*Trim extra space from the end of the string s (in place)*/
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
}

 /*Trim extra space from both ends of the string s (in place)*/
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}

/* Global variables for signal handling, verbose mode tracking and pthread mutex locks*/
static volatile int keep_running = 1;
static volatile int all_fds[100] = {0};
static volatile int v_flag = 0;
static volatile int prim_id = -1;
static volatile int main_thread_fd = 0;
static volatile int self_id = -1;
string n_type = "", self_forward_ip = "";
int server_cnt = 0;
int self_forward_port = -1;
vector<addr_info*> server_bind_info;
vector<addr_info*> server_forward_info;
BigTable big_table;
vector<int> active_clients; // store active front-end server index
vector<addr_info*> all_subs; // store all subordinate server index
vector<string> all_subs_full_ip;
map<string, int> server_forward_addrs_to_id_map;
map<string, pthread_mutex_t> *all_user_locks  = new map<string, pthread_mutex_t>();
pthread_mutex_t table_mutex_lock;
  


/* Check whether string s1 starts with s2*/
bool start_with(const char *s1, const char *s2)
{
   if(strncmp(s1, s2, strlen(s2)) == 0) return true;
   return false;
}

/* Construct an address information struct from a given full IP address */
struct addr_info* getAddrInfo(string ip_port){
  size_t found_colon = ip_port.find(":");
  if(found_colon == string::npos){
    throw "Invalid input server address!";
  }
  struct addr_info* info = new addr_info();
  info->ip = ip_port.substr(0, found_colon);
  info->port = atoi((ip_port.substr(found_colon + 1)).c_str());
  return info;
}

/* Signal handler for Ctrl+C, set the keep_running flag to be 0, letting all running worker threads know it's time to 
finish the current work and shut down, and clean up the resources for every worker thread*/
void control_shutdown(int arg){
  keep_running = 0;  
  
  for(int i = 0; i < 100; i++){
    if(all_fds[i] != 0){
      int sockfd = all_fds[i];
      char shutdown_msg[] = "421 localhost Service not available, closing transmission channel\r\n";
      int flags = fcntl(sockfd, F_GETFL, 0);
      fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
      write(sockfd, shutdown_msg, strlen(shutdown_msg));
      close(sockfd);
      all_fds[i] = 0;
    }
  }
  int flags = fcntl(main_thread_fd, F_GETFL, 0);
  fcntl(main_thread_fd, F_SETFL, flags | O_NONBLOCK);
  
   // destroy mutex locks for all users
   map<string, pthread_mutex_t>::iterator it;
   pthread_mutex_lock(&table_mutex_lock);
  for (it = (*all_user_locks).begin(); it != (*all_user_locks).end(); it++){
    pthread_mutex_destroy(&(it->second));
  }
    pthread_mutex_unlock(&table_mutex_lock);
    pthread_mutex_destroy(&table_mutex_lock);
  
}

/* If current thread receives the Ctrl+C signal, it invokes the signal handler. Otherwise, it unpack the arguments and start handling each client commands according to SMTP RFC protocol. 
  After the data arrives, it will try to get mutex lock for every recipient email file it needs to write to, if one of the attempts fails, it will return error to client.
*/
void* client_worker(void* arg){
  
  signal(SIGINT, control_shutdown);
  read_args* r_args = (read_args* ) arg;
  read_args th_args = *r_args;
  int comm_fd = th_args.fd;
  int v_flag = th_args.v_flag;
  int ind = th_args.index;
  
  char buf[10000];
  memset(buf, 0, 10000);

  if(v_flag){
    fprintf(stderr, "[%d] Connection closed\r\n", comm_fd);
  }
  
  close(comm_fd);
  pthread_exit(NULL);
}

void* sub_server_worker(void* arg){
  
  signal(SIGINT, control_shutdown);
  read_args* r_args = (read_args* ) arg;
  read_args th_args = *r_args;
  int comm_fd = th_args.fd;
  int v_flag = th_args.v_flag;
  int ind = th_args.index;
  
  char buf[10000];
  memset(buf, 0, 10000);

  if(v_flag){
    fprintf(stderr, "[%d] Connection closed\r\n", comm_fd);
  }
  
  close(comm_fd);
  pthread_exit(NULL);
}

void* prim_server_worker(void* arg){
  
  signal(SIGINT, control_shutdown);
  read_args* r_args = (read_args* ) arg;
  read_args th_args = *r_args;
  int comm_fd = th_args.fd;
  int v_flag = th_args.v_flag;
  int ind = th_args.index;
  
  char buf[10000];
  memset(buf, 0, 10000);

  if(v_flag){
    fprintf(stderr, "[%d] Connection closed\r\n", comm_fd);
  }
  

  close(comm_fd);
  pthread_exit(NULL);
}

/* Main thread parse the terminal arguments including verbose mode, port number and directory, start a socket, bind to given port and listen for connections.
  For each connection, it starts a new worker thread and let it handle all the requests.
  If Ctrl + C signal handler is invoked, main thread will clean up its own resources and exit.
*/
int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "*** Author: Jiaying Guo (gjying)\n");
    // cleanup();
    exit(1);
  }
  
  // parse arguments of command line
  int c;
  n_type = "subordinate";
  while ((c = getopt (argc, argv, "vo:")) != -1){
    switch (c){
       case 'o':
        n_type = string(optarg);
        break;
      case 'v':
        v_flag = 1;
        break;
      case '?':
        if (optopt == 'o')
          fprintf (stderr, "Option -p needs an argument!\n");
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n",optopt);
          return -1;
        default:
          abort ();
     }
  }
  
  
  if(optind >= argc){
  fprintf(stderr, "Invalid terminal input. Please check and try again!\n");
    exit(1);
  return 1;
  }

  // read from the config file to find the master server, if it's primary, get the subordinates list of indices, else get the primary index
  string master_server_for= "", master_server_bind = "";
  string master_server_ip = "";
  int master_server_port = 0;
  vector<string> sub_bind_strs;
  vector<string> sub_forward_strs;

  // read from config file, get the forward and bind address of current server and of all other servers
  ifstream file(argv[optind]);
  self_id = atoi(argv[optind + 1]);
  if(file.fail()){
    fprintf(stderr, "Cannot open config file.\n");
    // cleanup();
    exit(1);
  }
  
  string line;
  server_cnt = 0;
  while(getline(file, line)){
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

    size_t comma_pos = line.find(",");
    // config file line format 1: forward_addr binding_addr
    if(comma_pos != string::npos){

      server_bind_info.push_back(getAddrInfo(line.substr(comma_pos + 1)));
      server_forward_info.push_back(getAddrInfo(line.substr(0, comma_pos)));
      // bind_strs.push_back(line.substr(comma_pos + 1));
      // forward_strs.push_back(line.substr(0, comma_pos));
    }
    server_cnt++;
  }

  if(server_cnt < self_id){
    fprintf(stderr, "%s\n", "Current file doesn't support your input index!");
    // cleanup();
    exit(1);
  }
    
  

  // build up current server IP, port information 
  string self_ip = server_bind_info[self_id - 1]->ip;
  int self_port = server_bind_info[self_id - 1]->port;
  self_forward_ip = server_forward_info[self_id - 1]->ip;
  self_forward_port = server_forward_info[self_id - 1]->port;



  // build up master server socket
  struct sockaddr_in master_dest;
  bzero(&master_dest, sizeof(master_dest));
  master_dest.sin_family = AF_INET;
  master_dest.sin_addr.s_addr = htons(INADDR_ANY);
  master_dest.sin_port = htons(server_forward_info[0]->port);
  inet_pton(AF_INET, (server_forward_info[0]->ip).c_str(), &(master_dest.sin_addr));

  // open TCP socket
  struct protoent *protocol = getprotobyname("TCP");
  int listen_fd = socket(PF_INET, SOCK_STREAM, protocol->p_proto);
  if (listen_fd < 0) {
    fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
    exit(1);
  }
  main_thread_fd = listen_fd;
 
  // bind to self binding port
  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htons(INADDR_ANY);
  servaddr.sin_port = htons(self_port);
  bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  
  // listen
  listen(listen_fd, 100);
  signal(SIGINT, control_shutdown);
  bool get_prim = false,  primary_flag = false, finished_probe_master = false;
  
  // accept connections
  while(keep_running){
    
    // keep asking master server for primary info, otherwise won't start processing front-end requests
    while(!finished_probe_master){

      if(!get_prim){
        string msg = "GET_PRIM," + to_string(self_id - 1) + "\r\n";
        sendto(listen_fd,  msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&master_dest, sizeof(master_dest)); 
        get_prim = true;
      }

      struct sockaddr_in clientaddr;
      socklen_t clientaddrlen = sizeof(clientaddr);
      int comm_fd = accept(listen_fd, (struct sockaddr*)&clientaddr, &clientaddrlen); 
      string client_ip(inet_ntoa(clientaddr.sin_addr));
      int client_port = ntohs(clientaddr.sin_port);

      // if the current connection comes from master server
      if(client_ip.compare((server_forward_info[0])->ip) && client_port == (server_forward_info[0]->port)){
        char buf[10000];
        memset(buf, 0, 10000);
        int len = 0;
        while(!finished_probe_master){
          int recv = read(comm_fd, buf + len, 10000 - len); 
          len = strlen(buf);
          while(true){
            len = strlen(buf);
            if(len == 0) break;
            bool first_linebreaker = false;
            int index_of_first_endline = 0;
                 
            if(v_flag){
              fprintf(stderr, "[%d] C: %s\r\n", comm_fd, buf);
            }
              
            while(index_of_first_endline < strlen(buf) - 1){
              if(buf[index_of_first_endline] == '\r' && buf[index_of_first_endline + 1] == '\n'){
                first_linebreaker = true;
                break;
              }
              index_of_first_endline++;
            }
          
            //if not a complete line yet, continue read from client
            if(!first_linebreaker){
              break;
            }
            string line(buf, index_of_first_endline + 2);

            if(start_with(line.c_str(), "GET_PRIM")){
              size_t prim_pos = line.find(",");
              int prim = atoi(line.substr(0, prim_pos).c_str());
              prim_id = prim;
              if(prim == self_id){
                primary_flag = true;
                // if it's a primary node try to get the all subs from master server
                string req =  "LIST_SUB," + to_string(self_id - 1) + "\r\n";
                sendto(listen_fd,  req.c_str(), strlen(req.c_str()), 0, (struct sockaddr*)&master_dest, sizeof(master_dest)); 
              }else{
                finished_probe_master = true;
                close(comm_fd);
                break;
              } 
            }else if(start_with(line.c_str(), "LIST_SUB")){
              // reconstruct vector subs from sender:
              size_t start_pos = 0;
              size_t end_pos = 0;
              while(start_pos < line.length()){
                end_pos = line.find(",", start_pos);
                int curr_num = atoi(line.substr(start_pos, end_pos - start_pos).c_str());
                all_subs.push_back(server_forward_info[curr_num]);
                string curr_full_ip = (server_forward_info[curr_num])->ip + ":" + to_string((server_forward_info[curr_num])->port);
                all_subs_full_ip.push_back(curr_full_ip);
                start_pos = end_pos + 1;
              }
              finished_probe_master = true;
              close(comm_fd);
              break;
            }

            // move the rest of string back to the beginning of the buffer if there are msgs left
            if(len - index_of_first_endline - 2 > 0){
              char afterString[len];
              memset(afterString, 0, len);
              strcpy(afterString, &buf[index_of_first_endline + 2]);
              memset(buf, 0, 10000);
              strcpy(buf, afterString);
            }
            else{
              memset(buf, 0, 10000);
              len = 0;
              break;
            }
          }
        }
      } 
    }

    //
    int index = 0;
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);
    int comm_fd = accept(listen_fd, (struct sockaddr*)&clientaddr, &clientaddrlen); 
    string ip(inet_ntoa(clientaddr.sin_addr));
    int port = ntohs(clientaddr.sin_port);
    string curr_full_ip = ip + ":" + to_string(port);

     // send a greeting message after connection:
    char greeting[] = "220 localhost Service ready\r\n";
    write(comm_fd, greeting, strlen(greeting));
    if(v_flag){
      fprintf(stderr, "[%d] New Connection\r\n", comm_fd);
    }

    pthread_t thread;
    read_args input;
    input.fd = comm_fd;
    input.v_flag = v_flag;
    input.index = index;

    if(primary_flag){
      if(find(all_subs_full_ip.begin(), all_subs_full_ip.end(),curr_full_ip) != all_subs_full_ip.end()){
        pthread_create(&thread, NULL, sub_server_worker, &input);
        pthread_detach(thread);
      }else{
         pthread_create(&thread, NULL, client_worker, &input);
         pthread_detach(thread);
      }
    }else{
      string prim_full_ip = (server_forward_info[prim_id])->ip + ":" + to_string((server_forward_info[prim_id])->port);
      if(curr_full_ip.compare(prim_full_ip) == 0){
        pthread_create(&thread, NULL, prim_server_worker, &input);
        pthread_detach(thread);
      }else{
         pthread_create(&thread, NULL, client_worker, &input);
         pthread_detach(thread);
      }
    }
    

  }
  
  close(listen_fd);
  return 0;
}