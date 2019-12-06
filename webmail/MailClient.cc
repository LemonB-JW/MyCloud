#include "MailClient.h"

MailClient::MailClient(std::shared_ptr<Channel> channel) : stub_(Mail::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
std::vector<MailItem> MailClient::requestMailList(const std::string& user) {
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

std::string MailClient::requestMail(const std::string& user, const std::string& email_id) {

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

std::string MailClient::sendMail(const std::string& receiver, const std::string& created_time, const std::string& subject, 
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


std::string MailClient::deleteMail(const std::string& user, const std::string& email_id, const std::string& subject) {

  DeleteMailRequest request;
  request.set_user(user);
  request.set_id(email_id);
  request.set_subject(subject);


    // Container for the data we expect from the server.
  DeleteMailReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
  ClientContext context;

    // The actual RPC.
  Status status = stub_->DeleteMail(&context, request, &reply);

    // Act upon its status.
  if (status.ok()) {
    return reply.res();
  } else {
    std::cout << status.error_code() << ": " << status.error_message() << std::endl;

    return "Unable to delete the email!";
  }
}



std::vector<MailItem> MailClient::ListMailFromReply(const mail::GetMailListReply& mail_reply) {
  std::vector<MailItem> emails;

  for (int i = 0; i < mail_reply.item_size(); i++) {
    const mail::Email& email = mail_reply.item(i);

    // std::cout << "From: " << email.from() << std::endl;
    // std::cout << "Subject: " << email.subject() << std::endl;
    // std::cout << "Date: " << email.date() << std::endl;

    MailItem item(email.from(), email.subject(), email.date(), email.id());
    emails.push_back(item);

  }

  return emails;
}




// int main(int argc, char** argv) {
//   // Instantiate the client. It requires a channel, out of which the actual RPCs
//   // are created. This channel models a connection to an endpoint (in this case,
//   // localhost at port 50051). We indicate that the channel isn't authenticated
//   // (use of InsecureChannelCredentials()).
//   MailClient greeter(grpc::CreateChannel(
//       "localhost:50051", grpc::InsecureChannelCredentials()));
//   std::string user("Jill");
//   std::vector<MailItem> emails = greeter.requestMailList(user);
//   // Email reply = greeter.GetMail(user);
//   // std::cout << "Greeter received: " << reply.from() << std::endl;
//   std::cout << "Greeter received: " << emails.size() << std::endl;

//   return 0;
// }
