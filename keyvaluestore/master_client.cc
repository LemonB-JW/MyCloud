#include "master_client.h"
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;

int MBcommuClient::get_prim(int myindex){
	std::unique_ptr<MasterBackend::Stub> stub_;
	GetPrimRequest request;
	
	request.set_my_index(myindex);
	ClientContext context;
	GetPrimReply reply;
	Status status = stub_->get_prim(&context, request, &reply);
	
	if(status.ok()){
		return reply.prim_index();
	}else{
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
		return -1;
	}
}

std::vector<int> MBcommuClient::list_sub(int myindex){
	std::unique_ptr<MasterBackend::Stub> stub_;
	ListSubRequest request;
	
	request.set_my_index(myindex);
	ClientContext context;
	ListSubReply reply;
	Status status = stub_->list_sub(&context, request, &reply);
	
	if(status.ok()){
		std::vector<int> response;
		for (int i = 0; i< reply.sub_index_size(); i++){
			response.push_back(reply.sub_index(i));
		}
		return response;
	}else{
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
		std::vector<int> err;//return empty vector when error???
		return err;
	}
}
	
