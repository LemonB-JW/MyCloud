#include <stdio.h>
#include <string>
#include <vector>
#include <functional>

#include <grpcpp/grpcpp.h>
#include "masterBackend.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;

class MBcommuClient {
	public:
		MBcommuClient(std::shared_ptr<Channel> channel):stub_(MasterBackend::NewStub(channel)){}
	
	int get_prim(int myindex){
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
	
	std::vector<int> list_sub(int myindex){
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
			fprintf(stderr, "size of response %d\n", reply.sub_index_size());
			return response;
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			std::vector<int> err;//return empty vector when error???
			return err;
		}
	}
	
	private:
		std::unique_ptr<MasterBackend::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // 0.0.0.0:5000). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  std::string address("127.0.0.1:10001");//here shoule be the master address and port
  MBcommuClient client(
  	grpc::CreateChannel(
      address,
      grpc::InsecureChannelCredentials()
    )
  );
  int myIndex = 1;
  //fprintf(stderr, "ready to send alice to server\n");
  int primeIndex = client.get_prim(myIndex);
  std::vector<int> sublist = client.list_sub(primeIndex);
  
  std::cout << "Client received: " << primeIndex << "  sub list is "<<std::endl;
	for (int i = 0; i <  sublist.size(); i++){
		std::cout << sublist[i] << " " <<std::endl;
	}
  return 0;
}
