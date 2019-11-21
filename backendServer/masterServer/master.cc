#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include "../../lib/masterInfo.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

#define MAX_CONNECTIONS 100
#define MAX_COMMAND_LENGTH 1000

bool shutDown = false; //true if ctrl-c received
bool debugMode = false; //print debug msg if true
int socketfd;
masterInfo myInfo;
std::vector<int> threadID;


void sigintHandler(int sig_num);
void sigusr1Handler(int sig_num);

int main(int argc, char *argv[]) {
	/* Parse arguments */
  if (argc < 2)
    panic(stderr, "*** Final Project T08, Author: Peng Li (pl279)\n");
  /* Your code here */
  /************ Signal handler *************/
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigintHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	
  /************ Parse arguments *************/
	int opt;
	while((opt = getopt(argc, argv, "v")) != -1){
		switch(opt){
			case 'v':
				debugMode = true;
				break; 
			default:
				panic("Syntax: %s [-v] [-o ordering] <serverListFile> <index>\n", argv[0]);
		}	
	}
	
  if (optind >= argc){
		panic("Error: config file is missing!\n");
	}
	/* Read the server list */
	myInfo.readConfig(argc[optind]);
	
	//open server sockets
 	socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockFD <= 0)
  	panic("Cannot open bind socket (%s)\n", strerror(errno));
  
  //------------------set socket option-------------------
  int optval = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval))) 
		panic("Set socket option to SO_REUSEADDR and SO_REUSEPORT failed (%s)\n", strerror(errno)); 
	
	//===============bind() associates a socket with a specific port=========
  if (bind(socketfd, (struct sockaddr*)&myInfo.master_addr, sizeof(myInfo.master_addr)) < 0){ 
  	panic("Cannot bind to %s:%d (%s)\n", inet_ntoa(myInfo.master_addr.sin_addr.s_addr), myInfo.port, strerror(errno));
  }
  
  //==============listen() puts a socket into the listening state==========
  if (listen(socketfd, MAX_CONNECTIONS) < 0)  
  	panic("Cannot enter listening state %s:%d (%s)\n", inet_ntoa(myInfo.master_addr.sin_addr.s_addr), myInfo.port, strerror(errno));
  /*
  	create a thread for grpc frontend communication
  */	
  
  
  /*main loop*/
  while(!shutDown){
  	struct sockaddr_in client_addr;
  	int len = sizeof(client_addr);
  	int connfd = accept(socketfd, (struct sockaddr*)&client_addr, &len);
  	
  	if (connfd < 0)
  		panic("Master accept failed...(%s)\n", strerror(errno));
  	threadID.push_back(0);
  	if (pthread_create(&threadID[threadID.size()-1], NULL, threadWorker, &connfd)){
  		panic("Failed to create thread\n");
  	}
  	
  }
  
  
  close(socketfd);
}

void* threadWorker(void* arg){
	struct sigaction sigUsr1Handler;
  sigUsr1Handler.sa_handler = sigusr1Handler;
  sigemptyset(&sigUsr1Handler.sa_mask);
  sigUsr1Handler.sa_flags = 0;
	sigaction(SIGUSR1, &sigUsr1Handler, NULL);
	
	int comm_fd = arg;
	pthread_t tid = pthread_self();
	int bytesInBuf = 0;
	int crlfpos = 0;
	int buf[MAX_COMMAND_LENGTH];
	int endpos = 0;
	
	while(!shutDown){
		
		bytesInBuf = bytesInBuf - crlfpos - 1;
		if (bytesInBuf<0) bytesInBuf = 0;
		crlfpos = 0;
		//keep reading until \r\n
		while(!shutDown){
			for (int i = 0; i < bytesInBuf; i++){
				if(buf[i] == '\n' && i > 0){
					if( buf[i-1] =='\r'){
						crlfpos = i;
						break;
					}
				}
			}
			
			if (crlfpos > 0 || shutDown) break;
			if(bytesInBuf >= MAX_COMMAND_LENGTH) panic("Read %d bytes, but no CRLF found.\r\n", bytesInBuf);
			bytesRead = recv(fd, &buf[bytesInBuf], MAX_COMMAND_LENGTH - bytesInBuf, 0);
			if (bytesRead <= 0) panic("Read failed (%s)\n", strerror(errno));
			
		}//end of find CRLF while loop 
		if (shutDown) break;
		//found CRLF
		if (crlf > 0){
			if (match("GET_PRIME,*", buf) {
				//reply the the prime 
				char* scomd = strtok(buf, ",");
				char* sid = strtok(NULL, "\r\n");
				int serverid = atoi(sid);
				
				char sendbuf[MAX_COMMAND_LENGTH];
				sprintf(sendbuf, "GET_PRIME,%d", myInfo.getPrime(serverid));
				writeToclient(comm_fd, sendbuf); 
				
			}else if (match("LIST_SUB,*", buf)) {
				//reply the sub
				char* scomd = strtok(buf, ",");
				char* sid = strtok(NULL, "\r\n");
				int primeId = atoi(sid);
				
				char sendbuf[MAX_COMMAND_LENGTH];
				std::vector<int> subVec = myInfo.getSub(primeId);
				std::string subInString;
				///////////////////
				sprintf(sendbuf, "LIST_SUB,%s\r\n", subInstring.c_str());
				writeToclient(comm_fd, sendbuf); 
			}
			
			//remove handled command
			for(int i = 0; i <(bytesInBuf - crlfpos - 1); i++){	
				buf[i] = buf[crlfpos+i+1];
				buf[crlfpos+i+1] = '\0';
			}
		}
		
	}//end of outter while
	
	fprintf("exit\r\n");
	pthread_exit(NULL);
}


//=====================match=======================
bool match(const char *data, char *buf){
	bool matchCheck = true;
	int argptr = 0, bufptr = 0;
	while(matchCheck && data[argptr]){
		if(data[argptr] == '*')
			break;
		if(data[argptr++] != buf[bufptr++])
			matchCheck = false;
		}
	}
	
	if (!data[argptr] && buf[bufptr]){
    	matchCheck = false;
  }
	return matchCheck;
}

//****************write message to client**************
void writeToclient(int fd, const char *data){
	int len = strlen(data);
	int wptr = 0;
	while (wptr < len) {
    int w = send(fd, &data[wptr], len-wptr, 0);
  	if (w<0){
    	panic("Cannot write to conncetion (%s)\r\n", strerror(errno));
		}
  	if (w==0){
    	panic("Connection closed unexpectedly\r\n");
		}
  	wptr += w;
	}	
	/*if(debugMode){
		fprintf(stderr, "[%d] S: %.*s", fd, len, data);
	}*/
}

/* Signal Handler for SIGINT ----- Ctrl-C*/
void sigintHandler(int sig_num){ 
	shutDown = true;
}

/* Signal Handler for SIGUSR1-----------doing nothing just to unblock worker */
void sigusr1Handler(int sig_num){
	return;
}
