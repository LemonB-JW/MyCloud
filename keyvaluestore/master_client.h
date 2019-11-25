#include <stdio.h>
#include <string>
#include <vector>
#include <functional>
#include <grpcpp/grpcpp.h>
#include "masterBackend.grpc.pb.h"

using grpc::Channel;
using masterBackend::MasterBackend;

class MBcommuClient {

	// private:
		
	public:
		
		MBcommuClient(std::shared_ptr<Channel> channel):stub_(MasterBackend::NewStub(channel)){};
		int get_prim(int myindex);
		std::vector<int> list_sub(int myindex);

	
};
