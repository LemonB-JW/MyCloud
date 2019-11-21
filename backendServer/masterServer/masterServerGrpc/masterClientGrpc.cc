#include <stdio.h>
#include <string>

#include <grpcpp/grpcpp.h>
#include <functional>
#include "masterFrontend.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterFrontend::getKVipport;
using masterFrontend::frontendRequest;
using masterFrontend::masterReply;


class MFcommuClient {
	public:
		MFcommuClient(std::shared_ptr<Channel> channel):stub_(getKVipport::NewStub(channel)){}
	
	std::string receive_request(std::string username){
		frontendRequest request;
		
		request.set_user_name(username);
		fprintf(stderr, "here I am\n");
		ClientContext context;
		masterReply reply;
		Status status = stub_->receive_request(&context, request, &reply);
		
		if(status.ok()){
			return reply.server_ipport();
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			std::string res("GRPC FAILED");
			return res;
		}
	}
	private:
		std::unique_ptr<getKVipport::Stub> stub_;
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
  fprintf(stderr, "ready to send alice to server\n");
  std::string response = client.receive_request(myuser);
  std::cout << "Client received: " << myuser << "  server list is "<< response << std::endl;

  return 0;
}
