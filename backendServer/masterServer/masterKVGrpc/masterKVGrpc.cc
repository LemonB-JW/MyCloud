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

#include "masterBackend.grpc.pb.h"


#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

#define MAX_CONNECTIONS 100
#define MAX_COMMAND_LENGTH 1000

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;


bool shutDown = false; //true if ctrl-c received
bool debugMode = false; //print debug msg if true
int socketfd;
masterInfo myInfo;

class MFcommu final : public MasterBackend::Service{
	Status get_prim(
		ServerContext* context,
		const GetPrimRequest* request,
		GetPrimReply* reply
	)override{
		//std::string username = getServerList(request->user_name());
		int primInd = myInfo.getPrime(request->my_index());
		reply->set_prim_index(primInd);
		return Status::OK;
	}
	
	Status list_sub(
		ServerContext* context,
		const ListSubRequest* request,
		ListSubReply* reply
	)override{
		std::vector<int> sublist = myInfo.getSub(request->my_index());
		for (int i = 0; i < sublist.size(); i++){
			reply->add_sub_index(sublist[i]);
			//reply->set_sub_index(sublist[i]);
		}
		fprintf(stderr, "size of reply msg %d\n", reply->sub_index_size());
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
	Run();
	return 0;
}


void Run(){
	//std::string address("0.0.0.0:5000");
	std::string address(myInfo.mb_addr);
	fprintf(stderr, "into run\n");
	MFcommu service;
	
	//bind server to port and servicecd 
	ServerBuilder builder;
	
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	
	std::unique_ptr<Server> server(builder.BuildAndStart());
	fprintf(stderr, "Server listening on port: %s\n", address.c_str());
	
	server->Wait();
}

