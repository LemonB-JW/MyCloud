#include <stdio.h>
#include <string>
#include <functional>

#include <grpcpp/grpcpp.h>
#include "masterFrontend.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterFrontend::MasterFrontend;
using masterFrontend::getServerListRequest;
using masterFrontend::getServerListReply;


class MFcommuClient {
	public:
		MFcommuClient(std::shared_ptr<Channel> channel):stub_(MasterFrontend::NewStub(channel)){}
	
	std::vector<std::string> getServerList(std::string username){
		getServerListRequest request;
		
		request.set_user_name(username);
		fprintf(stderr, "here I am\n");
		ClientContext context;
		getServerListReply reply;
		Status status = stub_->getServerList(&context, request, &reply);
		
		if(status.ok()){
			std::vector<std::string> res;
			for (int i = 0; i < reply.server_ipport_size(); i++){
				res.push_back(reply.server_ipport(i));
			}
			return res;
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			std::string res("GRPC FAILED");
			std::vector<std::string> response;
			response.push_back(res);
			return response;
		}
	}
	
	private:
		std::unique_ptr<MasterFrontend::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // 0.0.0.0:5000). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  std::string address("127.0.0.1:10001");//here shoule be the master address and port
  MFcommuClient client(
  	grpc::CreateChannel(
      address,
      grpc::InsecureChannelCredentials()
    )
  );
  std::string myuser = "Alice";
  //fprintf(stderr, "ready to send alice to server\n");
  std::vector<std::string> response = client.getServerList(myuser);
  std::cout << "Client received: " << myuser << "  server list is "<< std::endl;
	for (int i = 0; i<response.size(); i++){
		fprintf(stderr, "%s ", response[i].c_str());
	}
	fprintf(stderr, "\n");
  return 0;
}
