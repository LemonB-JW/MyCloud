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

#include "SocketHelper.h"
using namespace std;

vector<string> forwarding_addrs;
vector<unsigned short> forwarding_ports;
vector<string> bind_addrs;
vector<unsigned short> bind_ports;

vector<pthread_t> vectorOfThreads;
vector<int> vectorOfSockets;

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
      printf("%s %s %s %s\n",
        line.substr(0, colon1).c_str(),
        line.substr(colon1 + 1, comma - colon1 - 1).c_str(),
        line.substr(comma + 1, colon2 - comma - 1).c_str(),
        line.substr(colon2 + 1, line.length() - colon2 - 1).c_str()
      );
    }
    else {
      int colon = line.find(':');
      string addr1 = line.substr(0, colon);
      int port1 = stoi(line.substr(colon + 1, line.length() - colon - 1));
      string addr2 = addr1;
      int port2 = port2;
      forwarding_addrs.push_back(addr1);
      forwarding_ports.push_back((unsigned short) port1);
      bind_addrs.push_back(addr1);
      bind_ports.push_back((unsigned short) port1);
      printf("%s %s %s %s\n",
        line.substr(0, colon).c_str(),
        line.substr(colon + 1, line.length() - colon - 1).c_str()
      );
    }
  }
  file.close();
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(stderr, "*** Author: Xuan Wang  (xuanw)\n");
    exit(1);
  }

  /* Your code here */
  string filename = string(argv[1]);
  int index = atoi(argv[2]);
  string bind_addr;
  int bind_port;

  // load files
  load_forwarding_and_bind_info(filename);
  
  // listen to the binding address and port
  bind_addr = bind_addrs[index - 1];
  bind_port = bind_ports[index - 1];

  int sock = socket_bind(bind_addr, bind_port);
  printf("Start listening to %s %d\n", bind_addr.c_str(), (int)bind_port);

  while (true) {
    // struct sockaddr_in src;
    // socklen_t srclen = sizeof(src);
    // char buf[100];
    // int rlen = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&src, &srclen);
    // buf[rlen] = 0;
    // printf("Echoing [%s] to %s %d\n", buf, inet_ntoa(src.sin_addr), src.sin_port);
    string addr;
    unsigned short port;
    string message = UDP_recv(sock, addr, port);
    UDP_send(sock, addr, port, message);
  }
  return 0;
}  