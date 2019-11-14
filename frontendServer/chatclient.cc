#include <stdio.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <unistd.h>
#include "SocketHelper.h"
using namespace std;

string server_addr;
unsigned short server_port;
int sock;

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "*** Author: Xuan Wang (xuanw)\n");
    exit(1);
  }

  /* load the server info (address and port) from the second command-line parameters */
  string server_info = string(argv[1]);
  int colon = server_info.find(':');
  server_addr = server_info.substr(0, colon);
  server_port = stoi(server_info.substr(colon + 1, server_info.length() - colon - 1));

  /* initialize socket */
  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
    exit(1);
  }
  struct sockaddr addr;
  socklen_t addrlen;
  getsockname(sock, &addr, &addrlen);
  struct sockaddr_in* p = (struct sockaddr_in*)&addr;
  string addr_s = inet_ntoa(p->sin_addr);
  int port_s = p->sin_port;
  printf("Bound info is %s %d\n", addr_s.c_str(), port_s);

  fd_set master;
  fd_set read_fds;
  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  FD_SET(0, &master);
  FD_SET(sock, &master); // s is a socket descriptor
  while(true) {
    read_fds = master;
    if (select(sock + 1,&read_fds,NULL,NULL,NULL) == -1) {
      perror("select:");
      exit(1);
    }
    // if there are any data ready to read from the socket
    if (FD_ISSET(sock, &read_fds)) {
      string addr;
      unsigned short port;
      string message = UDP_recv(sock, addr, port);
      printf("%s\n", message.c_str());
    }
    // if there is something in stdin
    if (FD_ISSET(0, &read_fds)) {
      string message;
      cin >> message;
      UDP_send(sock, server_addr, server_port, message);
    }
  }

  return 0;
}  