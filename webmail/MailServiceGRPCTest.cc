#include "MailServiceGRPC.h"
#include <iostream>
#include <memory>
#include <string>
#include "TableClient.h"
#include "../lib/FileMetaData.h"


#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "mail.grpc.pb.h"
#else
#include "mail.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using mail::GetMailListRequest;
using mail::GetMailListReply;
using mail::GetMailRequest;
using mail::GetMailReply;
using mail::PutMailRequest;
using mail::PutMailReply;
using mail::Mail;
using mail::Email;


int pflag = 0;
int aflag = 0;
int vflag = 0;
std::string master_addr;

void RunServer(unsigned int port_number) {
  std::string server_address = "127.0.0.1:" + std::to_string(port_number);

  MailServiceGRPC service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}



int main(int argc, char** argv) {

  int c;
  unsigned int port_number = 2500;

  // read in command line argument and process option
  while ((c = getopt(argc, argv, "vp:")) != -1) {
    switch (c) {
    case 'p':
      pflag = 1;
      port_number = atoi(optarg);
      break;
    case 'v':
      vflag = 1;
      break;
    case '?':
      if (isprint(optopt)) {
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      } else {
        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
      }
      return 1;
    default:
      break;
    }
  }


  if (optind == argc) {
    fprintf(stderr, "Missing master node address.\n");
    exit(1);
  }

  master_addr = string(argv[optind]);


  RunServer(port_number);

  return 0;
}