#include <stdio.h> //FILE type
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <string.h>

#include "masterInfo.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

int masterInfo::readConfig(const char* filename){
	// read file and find my ip and port
	FILE *infile = fopen(filename, "r");
	if (!infile) 
		panic("Cannot read server list from '%s'\n", filename);
	int numServers = 0;
	char linebuf[100];
	
	//the first line in the config file is master's address
	if (fgets(linebuf, 100, infile)!= NULL){
		char *sproxyaddr = strtok(linebuf, ",\r\n");
	  char *srealaddr = sproxyaddr ? strtok(NULL, ",\r\n") : NULL;
	  
	  char *sip = strtok(sproxyaddr, ":");
	  char *sport = strtok(NULL, ":\r\n");	
	  
	  master_addr.sin_family = AF_INET;
	  inet_aton(sip, &(master_addr.sin_addr));
	  master_addr.sin_port = htons(atoi(sport));
	}
	
	while	(fgets(linebuf, 100, infile)!= NULL){
		char *sproxyaddr = strtok(linebuf, ",\r\n");
	  char *srealaddr = sproxyaddr ? strtok(NULL, ",\r\n") : NULL;  
	  char *sip = strtok(sproxyaddr, ":");
	  char *sport = strtok(NULL, ":\r\n");	  
  
	  //store all forwarding address in server list
	  struct sockaddr_in temp;
	  temp.sin_family = AF_INET;
	  inet_aton(sip, &temp.sin_addr);
	  temp.sin_port = htons(atoi(sport));
	  serverlist.push_back(temp);
	}
	
	setPrimary();
}

void masterInfo::setPrimary(){
	int remainS = serverlist.size();
	
	while (remainS >= 6){
		remainS--;
		
	}
}
