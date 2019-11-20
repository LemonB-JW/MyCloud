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