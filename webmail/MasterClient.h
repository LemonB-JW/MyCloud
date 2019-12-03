#ifndef MASTERCLIENT_H
#define MASTERCLIENT_H

#include <stdio.h>
#include <string>
#include <functional>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "masterFrontend.grpc.pb.h"
#else
#include "masterFrontend.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterFrontend::MasterFrontend;
using masterFrontend::getServerListRequest;
using masterFrontend::getServerListReply;


class MasterClient {

	public:

		MasterClient(std::shared_ptr<Channel> channel);

		std::vector<std::string> getServerList(std::string username);

	private:
		std::unique_ptr<MasterFrontend::Stub> stub_;


};

#endif