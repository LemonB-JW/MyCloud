#include <stdio.h>
#include <unistd.h>//getopt
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <stdlib.h>
#include <netinet/in.h>

#include <string.h>//strerror
#include <pthread.h>
#include <functional>

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include <grpcpp/grpcpp.h>

#include "../../../lib/masterInfo.h"

#include "masterFrontend.grpc.pb.h"


#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

#define MAX_CONNECTIONS 100
#define MAX_COMMAND_LENGTH 1000

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using masterFrontend::getKVipport;
using masterFrontend::frontendRequest;
using masterFrontend::masterReply;


bool shutDown = false; //true if ctrl-c received
bool debugMode = false; //print debug msg if true
int socketfd;
masterInfo myInfo;
std::vector<int> threadID;
//getKVipport getKV;


std::string getServerList(std::string userName);

class MFcommu final : public getKVipport::Service{
	Status receive_request(
		ServerContext* context,
		const frontendRequest* request,
		masterReply* reply
	)override{
		//std::string username = receive_request(request->user_name());
		std::string serverlist = getServerList(request->user_name());
		fprintf(stderr, "get server list '%s'\n", serverlist.c_str());
		reply->set_server_ipport(serverlist);
		fprintf(stderr, "server replied\n");
		return Status::OK;
	}
};

void Run();

int main(int argc, char** argv){
	/* Parse arguments */
  if (argc < 2)
    panic("*** Final Project T08, Author: Peng Li (pl279)\n");
  /* Your code here */
  /************ Signal handler *************/
  /*struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = sigintHandler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	*/
  /************ Parse arguments *************/
	int opt;
	while((opt = getopt(argc, argv, "v")) != -1){
		switch(opt){
			case 'v':
				debugMode = true;
				break; 
			default:
				panic("Syntax: %s [-v] <serverConfigFile>\n", argv[0]);
		}	
	}
	
  if (optind >= argc){
		panic("Error: config file is missing!\n");
	}
	/* Read the server list */
	myInfo.readConfig(argv[optind]);
	
	//open server sockets
 	/*socketfd = socket(PF_INET, SOCK_STREAM, 0);
  if (socketfd <= 0)
  	panic("Cannot open bind socket (%s)\n", strerror(errno));
  
  //------------------set socket option-------------------
  int optval = 1;
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval))) 
		panic("Set socket option to SO_REUSEADDR and SO_REUSEPORT failed (%s)\n", strerror(errno)); 
	
	//===============bind() associates a socket with a specific port=========
  if (bind(socketfd, (struct sockaddr*)&myInfo.master_addr, sizeof(myInfo.master_addr)) < 0){ 
  	panic("Cannot bind to %s:%d (%s)\n", inet_ntoa(myInfo.master_addr.sin_addr), myInfo.port, strerror(errno));
  }
  
  //==============listen() puts a socket into the listening state==========
  if (listen(socketfd, MAX_CONNECTIONS) < 0)  
  	panic("Cannot enter listening state %s:%d (%s)\n", inet_ntoa(myInfo.master_addr.sin_addr), myInfo.port, strerror(errno));*/
  /*
  	create a thread for grpc frontend communication
  */	
  
  
  /*main loop*/
  
  

	Run();
	return 0;
}


void Run(){
	//std::string address("0.0.0.0:5000");
	std::string address("127.0.0.1:10001");
	fprintf(stderr, "into run\n");
	MFcommu service;
	
	//bind server to port and service
	ServerBuilder builder;
	
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	
	std::unique_ptr<Server> server(builder.BuildAndStart());
	fprintf(stderr, "Server listening on port: %s\n", address.c_str());
	
	server->Wait();
}

std::string getServerList(std::string userName){
	std::hash<std::string> str_hash;
	fprintf(stderr, "In get server list\n");
	int group = (str_hash(userName))%(myInfo.groupNum);
	fprintf(stderr, "group is %d\n", group);
	return myInfo.getServers(group);
}


