#include "MailClient.h"
#include "TableClient.h"
#include "MasterClient.h"
#include <iostream>
#include <memory>
#include <string>


int main(int argc, char** argv) {

  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).



	TableClient tableClient(grpc::CreateChannel(
		"127.0.0.1:5003", grpc::InsecureChannelCredentials()));

	std::string created_time = "Monday"; 
	int size = 1;
	std::string file_name = "Hello";
	std::string file_type = "email";
	std::string file_from = "sliu118";
	std::string user = "Jill";
	std::string file_content = "How are you?";


	std::string reply = tableClient.put(created_time, size, file_name, file_type, file_from, user, file_content);
	std::cout << "Reply is " << reply << std::endl;



	// MasterClient masterClient(grpc::CreateChannel(
	// 	"127.0.0.1:10001", grpc::InsecureChannelCredentials()));

	// std::string username("Jill");


	// std::vector<std::string> serverList = masterClient.getServerList(username);

	// std::cout << "Valid server size is " << serverList.size() << std::endl;

	// std::cout << "Valid server address is " << serverList[0] << std::endl;


	MailClient mailClient(grpc::CreateChannel(
		"127.0.0.1:4000", grpc::InsecureChannelCredentials()));
	std::string username("Jill");
	std::vector<MailItem> emails = mailClient.requestMailList(username);
	std::string content = mailClient.requestMail(username, reply);
	std::string res = mailClient.deleteMail(username, reply, file_name);

	std::cout << "MailClient received: " << emails.size() << std::endl;
	std::cout << "Mail content received: " << content << std::endl;
	std::cout << "Mail deleted : " << res << std::endl;

	return 0;


}