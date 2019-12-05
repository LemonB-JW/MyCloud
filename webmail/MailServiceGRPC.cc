#include "MailServiceGRPC.h"



  // retrieve a list of emails by calling BigTable's GRPC service
  Status MailServiceGRPC::GetMailList(ServerContext* context, const GetMailListRequest* request,
    GetMailListReply* reply) {


    // std::string serverAddress = getServerAddress(request->user());


    std::string serverAddress = "127.0.0.1:5002";


    //TableClient tableClient(grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials()));

    //std::vector<FileMetaData> emailList = tableClient.listEmails(request->user());

//    for (int i = 0; i < emailList.size(); i++) {
//      constructMailReply(reply->add_item(), emailList[i].file_from, emailList[i].file_name, emailList[i].created_time, emailList[i].file_id);
//    }

  constructMailReply(reply->add_item(), "Jill1", "Hello", "12/04/2019", "12345");
  constructMailReply(reply->add_item(), "Jill2", "Hello", "12/04/2019", "12346");
  constructMailReply(reply->add_item(), "Jill3", "Hello", "12/04/2019", "12347");
  constructMailReply(reply->add_item(), "Jill4", "Hello", "12/04/2019", "12348");
  constructMailReply(reply->add_item(), "Jill5", "Hello", "12/04/2019", "12349");
    return Status::OK;
  }

  // retrieve a single email by calling BigTable's GRPC service
  Status MailServiceGRPC::GetMail(ServerContext* context, const GetMailRequest* request,
    GetMailReply* reply) {


    // std::string serverAddress = getServerAddress(request->user());


    std::string serverAddress = "127.0.0.1:5002";

    //TableClient tableClient(grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials()));

    //std::string content = tableClient.getEmail(request->user(), request->email_id());

    std::string content = "Success";

    reply->set_content(content);

    return Status::OK;
  }

  Status MailServiceGRPC::PutMail(ServerContext* context, const PutMailRequest* request,
    PutMailReply* reply) {

    // std::string serverAddress = getServerAddress(request->receiver());

    std::string serverAddress = "127.0.0.1:5002";

    TableClient tableClient(grpc::CreateChannel(
      serverAddress, grpc::InsecureChannelCredentials()));

    std::string id = tableClient.put(request->created_time(), request->size(), request->subject(), 
      "email", request->sender(), request->receiver(), request->content());

    reply->set_email_id(id);

    return Status::OK;
  }

  Status MailServiceGRPC::DeleteMail(ServerContext* context, const DeleteMailRequest* request,
    DeleteMailReply* reply) {

    // std::string serverAddress = getServerAddress(request->receiver());

    std::string serverAddress = "127.0.0.1:5002";

    TableClient tableClient(grpc::CreateChannel(
      serverAddress, grpc::InsecureChannelCredentials()));

    //deleteEmail(std::string row, std::string col, std::string file_type, std::string path_name);

    std::string res = tableClient.deleteEmail(request->user(), request->id(), "email", request->subject());

    reply->set_res(res);

    return Status::OK;


  }



  // helper function to reconstruct email from BigTable's GRPC reply
  void MailServiceGRPC::constructMailReply(mail::Email* emailReply, std::string from, std::string subject, std::string date, std::string id) {
    emailReply->set_from(from);
    emailReply->set_subject(subject);
    emailReply->set_date(date);
    emailReply->set_id(id);
  }


  // helper function to return an IP address of a live backend server
  std::string MailServiceGRPC::getServerAddress(std::string username) {
     MasterClient masterClient(grpc::CreateChannel(
      "127.0.0.1:10001", grpc::InsecureChannelCredentials()));

     std::vector<std::string> validServers = masterClient.getServerList(username);

     if (validServers.size() == 0) {
      return NULL;
     }

     return validServers[0];

  }





// void RunServer(unsigned int port_number) {
//   std::string server_address = "127.0.0.1:" + std::to_string(port_number);

//   MailServiceGRPC service;

//   ServerBuilder builder;
//   // Listen on the given address without any authentication mechanism.
//   builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//   // Register "service" as the instance through which we'll communicate with
//   // clients. In this case it corresponds to an *synchronous* service.
//   builder.RegisterService(&service);
//   // Finally assemble the server.
//   std::unique_ptr<Server> server(builder.BuildAndStart());
//   std::cout << "Server listening on " << server_address << std::endl;

//   // Wait for the server to shutdown. Note that some other thread must be
//   // responsible for shutting down the server for this call to ever return.
//   server->Wait();
// }



// int main(int argc, char** argv) {

//   int c;
//   unsigned int port_number = 2500;

//   // read in command line argument and process option
//   while ((c = getopt(argc, argv, "vp:")) != -1) {
//     switch (c) {
//     case 'p':
//       pflag = 1;
//       port_number = atoi(optarg);
//       break;
//     case 'v':
//       vflag = 1;
//       break;
//     case '?':
//       if (isprint(optopt)) {
//         fprintf(stderr, "Unknown option `-%c'.\n", optopt);
//       } else {
//         fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
//       }
//       return 1;
//     default:
//       break;
//     }
//   }


//   if (optind == argc) {
//     fprintf(stderr, "Missing master node address.\n");
//     exit(1);
//   }

//   master_addr = string(argv[optind]);


//   RunServer(port_number);

//   return 0;
// }
