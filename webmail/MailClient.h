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
using mail::DeleteMailRequest;
using mail::DeleteMailReply;
using mail::Mail;
using mail::Email;


class MailClient {

public:

	MailClient(std::shared_ptr<Channel> channel);

	std::vector<MailItem> requestMailList(const std::string& user);

	std::string requestMail(const std::string& user, const std::string& email_id);

	std::string sendMail(const std::string& receiver, const std::string& created_time, const std::string& subject, 
    const int& size, const std::string& sender, const std::string& content);

    std::string deleteMail(const std::string& user, const std::string& email_id, const std::string& subject);

    std::vector<MailItem> ListMailFromReply(const mail::GetMailListReply& mail_reply);

private:
	std::unique_ptr<Mail::Stub> stub_;

};