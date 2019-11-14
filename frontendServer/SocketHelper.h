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
using namespace std;

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

void UDP_send(int sock, string addr, unsigned short port, string message)
{
  printf("Sended a UDP package to %s %d\n", addr.c_str(), port);
  struct sockaddr_in dest;
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  inet_pton(AF_INET, addr.c_str(), &(dest.sin_addr));
  dest.sin_port = htons(port);
  sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&dest, sizeof(dest));
}

string UDP_recv(int sock, string& addr, unsigned short& port)
{
    struct sockaddr_in src;
    socklen_t srclen = sizeof(src);
    char buf[1000];
    int rlen = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&src, &srclen);
    buf[rlen] = 0;
    addr = inet_ntoa(src.sin_addr);
    port = ntohs(src.sin_port);
    printf("Received a UDP package to %s %d [%s]\n", addr.c_str(), port, buf);
    return string(buf);
}

