#pragma once

#include <iostream>
#include <errno.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <cctype>
#include <ctime>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <map> 
#include <arpa/inet.h>

// This macros will check the verbose status. It makes sure only outputting log
// when it is turned on
#define debug(a...) do { if (verbose) fprintf(stderr, a); } while (0)

using namespace std;

bool verbose = false;

// A wrapper for bind socket operation. It will start listen to addr:port after
// calling this function
int socket_bind(string addr, unsigned short port)
{
  int sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
    exit(1); 
  }
  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  inet_pton(AF_INET, addr.c_str(), &(servaddr.sin_addr));
  servaddr.sin_port = htons(port);
  bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
  return sock;
}

// A wrapper for UDP sendto operation.
// inet_pton() will convert the addr info from host byte order to network byte order
// htons() will convert the port info from host byte order to network byte order
void UDP_send(int sock, string addr, unsigned short port, string message)
{
  struct sockaddr_in dest;
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  inet_pton(AF_INET, addr.c_str(), &(dest.sin_addr));
  dest.sin_port = htons(port);
  sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&dest, sizeof(dest));
}

// A wrapper for UDP recvfrom operation
// inet_ntoa() will convert the addr info from network byte order to host byte order
// ntohs() will convert the port info from network byte order to host byte order
// It should be notice that there is a maximum message length limit here
string UDP_recv(int sock, string& addr, unsigned short& port)
{
    struct sockaddr_in src;
    socklen_t srclen = sizeof(src);
    char buf[1000];
    int rlen = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&src, &srclen);
    buf[rlen] = 0;
    addr = inet_ntoa(src.sin_addr);
    port = ntohs(src.sin_port);
    return string(buf);
}
