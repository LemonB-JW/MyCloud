/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

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
using mail::MailRequest;
using mail::MailReply;
using mail::Mail;
using mail::Email;

void ConstructMailReply(mail::Email* emailReply, std::string from, std::string subject, std::string date) {
  emailReply->set_from(from);
  emailReply->set_subject(subject);
  emailReply->set_date(date);
}


// Logic and data behind the server's behavior.
class MailServiceImpl final : public Mail::Service {
  Status GetMailList(ServerContext* context, const MailRequest* request,
    MailReply* reply) override {


    TableClient tableClient(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));

    std::vector<FileMetaData> emailList = tableClient.listEmails(request->user());

    for (int i = 0; i < emailList.size(); i++) {
      ConstructMailReply(reply->add_item(), emailList[i].file_from, emailList[i].file_name, emailList[i].created_time);
    }

    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MailServiceImpl service;

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
  RunServer();

  return 0;
}
