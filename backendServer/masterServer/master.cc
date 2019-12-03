#include <stdio.h>
#include <unistd.h>//getopt
#include <stdlib.h>
#include <signal.h>//signal
#include <string.h>//strerror
#include <pthread.h>


#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <sstream>

#include <grpcpp/grpcpp.h>

#include "../../lib/masterInfo.h"

#include "masterFrontend.grpc.pb.h"
#include "masterBackend.grpc.pb.h"
#include "backendMaster.grpc.pb.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

#define MAX_CONNECTIONS 100
#define MAX_COMMAND_LENGTH 1000

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using masterFrontend::MasterFrontend;
using masterFrontend::getServerListRequest;
using masterFrontend::getServerListReply;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;

using backendMaster::BackendMaster;
using backendMaster::EmptyRequest;
using backendMaster::HeartbeatReply;

bool shutDown = false; //true if ctrl-c received
bool debugMode = false; //print debug msg if true
int socketfd;
masterInfo myInfo;
pthread_t frontendThread;
pthread_t backendThread;


void sigintHandler(int sig_num);
void sigusr1Handler(int sig_num);
std::vector<std::string> getServers(std::string userName);


class BMcommuClient {
	public:
		BMcommuClient(std::shared_ptr<Channel> channel):stub_(BackendMaster::NewStub(channel)){}
	
	int heartbeat(){
		EmptyRequest request;
		
		//request.set_my_index(myindex);
		ClientContext context;
		HeartbeatReply reply;
		Status status = stub_->heartbeat(&context, request, &reply);
		
		if(status.ok()){
			return reply.checkpoint_v();
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			return -1;
		}
	}
	
	private:
		std::unique_ptr<BackendMaster::Stub> stub_;
};



class MFcommu final : public MasterFrontend::Service{
	Status getServerList(
		ServerContext* context,
		const getServerListRequest* request,
		getServerListReply* reply
	)override{
		//std::string username = getServerList(request->user_name());
		std::vector<std::string> serverlist = getServers(request->user_name());
		fprintf(stderr, "get server list:\n");
		for (int i = 0; i < serverlist.size(); i++){
			reply->add_server_ipport(serverlist[i]);
			fprintf(stderr, "%s ", serverlist[i].c_str());
		}
		fprintf(stderr, "\nserver replied\n");
		return Status::OK;
	}
};


class MBcommu final : public MasterBackend::Service{
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

void* RunF(void* arg);
void* RunB(void* arg);

int main(int argc, char *argv[]) {
	/* Parse arguments */
  if (argc < 2)
    panic("*** Final Project T08, Author: Peng Li (pl279)\n");
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
	myInfo.readConfig(argv[optind]);

  /*main loop*/
  if (pthread_create(&frontendThread, NULL, &RunF, NULL) != 0) 
  	panic("Error: failed to create frontend GRPC thread");
  	
  if (pthread_create(&backendThread, NULL, &RunB, NULL) != 0) 
  	panic("Error: failed to create backend GRPC thread");
  
  //loop listen to the backend servers' heartbeat
  //periodically listen to the heartbeat
  
  while(!shutDown){
  	for (int i = 0; i < myInfo.numServers(); i++){
  		std::string address(myInfo.getBMaddr(i));
  		
  		BMcommuClient client(
				grpc::CreateChannel(
				  address,
				  grpc::InsecureChannelCredentials()
				)
			);
			int temp_checkpoint_version = client.heartbeat();
			//TODO: update checkpoint version
			if (temp_checkpoint_version < 0){
				//TODO: add server index to dead list
			}else{
				//TODO: if server index in dead list: remove it from dead list and do recovery!!!
			}
  	}
  }
  
  //close this thread
  return 0;//double check
}


void* RunF(void* arg){
	//std::string address("0.0.0.0:5000");
	fprintf(stderr, "into runF\n");
	std::string addressF(myInfo.getMFaddr());
	MFcommu serviceFront;
	//bind server to port and service
	ServerBuilder builderF;
	builderF.AddListeningPort(myInfo.getMFaddr(), grpc::InsecureServerCredentials());
	builderF.RegisterService(&serviceFront);
	
	std::unique_ptr<Server> serverF(builderF.BuildAndStart());
	fprintf(stderr, "Master Server listening on port: %s\n", addressF.c_str());
	serverF->Wait();
}

void* RunB(void* arg){
	fprintf(stderr, "into runB\n");
	std::string addressB(myInfo.getMBaddr());
	MBcommu serviceBack;
	//bind server to port and service
	ServerBuilder builderB;
	builderB.AddListeningPort(myInfo.getMBaddr(), grpc::InsecureServerCredentials());
	builderB.RegisterService(&serviceBack);
	
	std::unique_ptr<Server> serverB(builderB.BuildAndStart());
	fprintf(stderr, "Master Server listening on port: %s\n", addressB.c_str());
	serverB->Wait();
}

void* heartbeat(void* arg){
	//signal handler here
	while(!shutDown){
		//loop: ask for heartbeat for every backend server every minute
		
		/*wait for grpc reply if failed, mark the server as down*/
		//TODO: add mutex in masterInfo, prevent reading and modifying at the same time
	}
	
	//exit thread
	//pthread_exit(heartbeatThread);
}

std::vector<std::string> getServers(std::string userName){
	std::hash<std::string> str_hash;
	fprintf(stderr, "In get server list, number of Group is%d\n", myInfo.getGroupNum());
	int group = (str_hash(userName))%(myInfo.getGroupNum());
	fprintf(stderr, "group is %d\n", group);
	return myInfo.getServers(group);
}

/* Signal Handler for SIGINT ----- Ctrl-C*/
void sigintHandler(int sig_num){ 
	shutDown = true;
	//pthread_kill(heatbeatThread, SIGUSR1);
}

/* Signal Handler for SIGUSR1-----------doing nothing just to unblock worker */
void sigusr1Handler(int sig_num){
	return;
}
