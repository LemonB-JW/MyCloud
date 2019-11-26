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
#include "MailItem.h"

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "mail.grpc.pb.h"
#else
#include "mail.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using mail::GetMailListRequest;
using mail::GetMailListReply;
using mail::GetMailRequest;
using mail::GetMailReply;
using mail::PutMailRequest;
using mail::PutMailReply;
using mail::Mail;
using mail::Email;


std::vector<MailItem> ListMailFromReply(const mail::GetMailListReply& mail_reply) {
  std::vector<MailItem> emails;

  for (int i = 0; i < mail_reply.item_size(); i++) {
    const mail::Email& email = mail_reply.item(i);

    // std::cout << "From: " << email.from() << std::endl;
    // std::cout << "Subject: " << email.subject() << std::endl;
    // std::cout << "Date: " << email.date() << std::endl;

    MailItem item(email.from(), email.subject(), email.date());
    emails.push_back(item);
   
  }

  return emails;
}


class MailClient {

 public:
  MailClient(std::shared_ptr<Channel> channel)
      : stub_(Mail::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::vector<MailItem> requestMailList(const std::string& user) {
    // Data we are sending to the server.
    GetMailListRequest request;
    request.set_user(user);

    // Container for the data we expect from the server.
    GetMailListReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetMailList(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return ListMailFromReply(reply);
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;

      std::vector<MailItem> emails;
      return emails;
    }
  }

  std::string requestMail(const std::string& user, const std::string& email_id) {

    // Data we are sending to the server.
    GetMailRequest request;
    request.set_user(user);
    request.set_email_id(email_id);

    // Container for the data we expect from the server.
    GetMailReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetMail(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.content();
    } else {
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;

      return "Could not find the email!";
    }

  }

  std::string sendMail(const std::string& receiver, const std::string& created_time, const std::string& subject, 
    const int& size, const std::string& sender, const std::string& content) {

    // Data we are sending to the server.
    PutMailRequest request;
    request.set_receiver(receiver);
    request.set_created_time(created_time);
    request.set_subject(subject);
    request.set_sender(sender);
    request.set_content(content);
    request.set_size(size);


    // Container for the data we expect from the server.
    PutMailReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->PutMail(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.email_id();
    } else {
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;

      return "Unable to deliver the email!";
    }

  }

 private:
  std::unique_ptr<Mail::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  MailClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string user("Jill");
  std::vector<MailItem> emails = greeter.requestMailList(user);
  // Email reply = greeter.GetMail(user);
  // std::cout << "Greeter received: " << reply.from() << std::endl;
  std::cout << "Greeter received: " << emails.size() << std::endl;

  return 0;
}
