#ifndef MAILSERVICEGRPC_H
#define MAILSERVICEGRPC_H

#include <iostream>
#include <memory>
#include <string>
#include "TableClient.h"
#include "MasterClient.h"
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

class MailServiceGRPC final : public Mail::Service {

	Status GetMailList(ServerContext* context, const GetMailListRequest* request,
    GetMailListReply* reply) override;

    Status GetMail(ServerContext* context, const GetMailRequest* request,
    GetMailReply* reply) override;

    Status PutMail(ServerContext* context, const PutMailRequest* request,
    PutMailReply* reply) override;

    void constructMailReply(mail::Email* emailReply, std::string from, std::string subject, std::string date);

    std::string getServerAddress(std::string username);

};

#endif