#include "MasterClient.h"



MasterClient::MasterClient(std::shared_ptr<Channel> channel):stub_(MasterFrontend::NewStub(channel)){}

std::vector<std::string> MasterClient::getServerList(std::string username) {

	getServerListRequest request;
	request.set_user_name(username);



	ClientContext context;
	std::vector<std::string> res;

	getServerListReply reply;
	Status status = stub_->getServerList(&context, request, &reply);

	if(status.ok()){
		for (int i = 0; i < reply.server_ipport_size(); i++){
			res.push_back(reply.server_ipport(i));
		}
		return res;
	}else{
		std::cout << status.error_code() << ": " << status.error_message() << std::endl;
		
		return res;
	}
}
	


// int main(int argc, char** argv) {
//   // Instantiate the client. It requires a channel, out of which the actual RPCs
//   // are created. This channel models a connection to an endpoint (in this case,
//   // 0.0.0.0:5000). We indicate that the channel isn't authenticated
//   // (use of InsecureChannelCredentials()).
//   std::string address("127.0.0.1:10001");//here shoule be the master address and port
//   MFcommuClient client(
//   	grpc::CreateChannel(
//       address,
//       grpc::InsecureChannelCredentials()
//     )
//   );
//   std::string myuser = "Alice";
//   //fprintf(stderr, "ready to send alice to server\n");
//   std::vector<std::string> response = client.getServerList(myuser);
//   std::cout << "Client received: " << myuser << "  server list is "<< std::endl;
// 	for (int i = 0; i<response.size(); i++){
// 		fprintf(stderr, "%s ", response[i].c_str());
// 	}
// 	fprintf(stderr, "\n");
//   return 0;
// }
