#include "../lib/DistributedStorage.h"
#include <sys/file.h>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <string>
#include <functional>

#include <grpcpp/grpcpp.h>
#include "masterBackend.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using masterBackend::MasterBackend;
using masterBackend::GetPrimRequest;
using masterBackend::GetPrimReply;
using masterBackend::ListSubRequest;
using masterBackend::ListSubReply;

class MBcommuClient {
	public:
		MBcommuClient(std::shared_ptr<Channel> channel):stub_(MasterBackend::NewStub(channel)){}
	
	int get_prim(int myindex){
		GetPrimRequest request;
		
		request.set_my_index(myindex);
		ClientContext context;
		GetPrimReply reply;
		Status status = stub_->get_prim(&context, request, &reply);
		
		if(status.ok()){
			return reply.prim_index();
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			return -1;
		}
	}
	
	std::vector<int> list_sub(int myindex){
		ListSubRequest request;
		
		request.set_my_index(myindex);
		ClientContext context;
		ListSubReply reply;
		Status status = stub_->list_sub(&context, request, &reply);
		
		if(status.ok()){
			std::vector<int> response;
			for (int i = 0; i< reply.sub_index_size(); i++){
				response.push_back(reply.sub_index(i));
			}
			return response;
		}else{
			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			std::vector<int> err;//return empty vector when error???
			return err;
		}
	}
	
	private:
		std::unique_ptr<MasterBackend::Stub> stub_;
};


/* Construct an address information struct from a given full IP address */
struct addr_info DistributedStorage::constructAddrInfo(std::string ip_port){
  size_t found_colon = ip_port.find(":");
  if(found_colon == std::string::npos){
    throw "Invalid input server address!";
  }
  struct addr_info info;
  info.ip = ip_port.substr(0, found_colon);
  info.port = atoi((ip_port.substr(found_colon + 1)).c_str());
  return info;
}

void DistributedStorage::readConfigFile(const char* config_file, const char* server_id){
	 // read from config file, get the forward and bind address of current server and of all other servers
	  std::string f_name(config_file);
	  ifstream file(config_file);
	  cout<<"server id is "<<config_file<<" "<<server_id<<endl;
	  server_index = atoi(server_id) - 1;
	  cout<<"server index is "<<server_index<<endl;
	  if(file.fail()){
	    fprintf(stderr, "Cannot open config file.\n");
	    exit(1);
	  }
	  std::string line;
	  while(getline(file, line)){
	    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
	    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
	    size_t comma_pos = line.find(",");
	    cout<<"comma pos is "<<comma_pos<<endl;
	    // config file line format 1: forward_addr binding_addr
	    if(comma_pos != string::npos){
	      all_server_front_addr.push_back(constructAddrInfo(line.substr(0, comma_pos)));
	      all_server_back_addr.push_back(constructAddrInfo(line.substr(comma_pos + 1)));
	    }
	    num_of_servers++;
	  }

	  master_addr.ip = all_server_back_addr.at(0).ip;
	  master_addr.port = all_server_back_addr.at(0).port;
	  self_addr.ip = all_server_back_addr.at(server_index).ip;
	  self_addr.port = all_server_back_addr.at(server_index).port;
	  cout<<"num of servers is "<<num_of_servers<<endl;
	  if(num_of_servers < server_index){
	    fprintf(stderr, "%s\n", "Current file doesn't support your input index!");
	    // cleanup();
	    exit(1);
	  }

	  // RPC call to get_prim and list_sub
	  std::string master_full_ip = master_addr.ip + ":" + std::to_string(master_addr.port);
	  MBcommuClient client(
	    grpc::CreateChannel(
	      master_full_ip,
	      grpc::InsecureChannelCredentials()
	    )
	  );
	  int primeIndex = client.get_prim(server_index - 1) + 1;
	  // int primeIndex = 1;
	  cout<<"Prime index is "<<primeIndex<<" server_index is "<<server_index<<" master full ip is "<<master_full_ip<<endl; 
	  updatePrimary(primeIndex);
	  if(is_primary){
	    std::vector<int> sublist= client.list_sub(primeIndex - 1);
	    cout<<"sublist size "<<sublist.size()<<endl;
	    for(int i = 0; i < sublist.size(); i++){
	    	cout<<"sublist value  is "<<sublist.at(i)<<endl;
	    }
	    // std::vector<int> sublist;
	    // sublist.push_back(2);
	    // sublist.push_back(3);
	    parseAllSubIndices(sublist);
	  }
}

void DistributedStorage::parseAllSubIndices(std::vector<int> all_sub_indices){
	cout<<"all sub indices size is "<< all_sub_indices.size()<<endl;
	for(int i = 0; i < all_sub_indices.size(); i++){
		cout<<"my sub is "<<all_server_back_addr.at(all_sub_indices.at(i) + 1).port<<endl;
		all_sub_addr.push_back(all_server_back_addr.at(all_sub_indices.at(i) + 1));
	}
}

void DistributedStorage::updatePrimary(int primary_id){
	
	if(primary_id == server_index) is_primary = true;
	primary_index = primary_id;
	cout<<"primary index is "<<primary_index<<"self id is "<<server_index<<endl;
	// primary_index = primary_id;
	primary_addr = new addr_info();
	primary_addr->ip = all_server_back_addr.at(primary_index).ip;
	primary_addr->port = all_server_back_addr.at(primary_index).port;
}

// bool DistributedStorage::localPut(string created_time, int size, string path_name, string file_type, string file_from, string row, string data){

// 	string file_id = table.put(created_time, size, path_name, file_type, file_from, row, data);
// 	return true;
// }

std::string DistributedStorage::localPut(std::string created_time, int size, std::string path_name, std::string file_type, std::string file_from, std::string row, std::string data){
	string file_id = table.put(created_time, size, path_name, file_type, file_from, row, data);
	cout<<"self id is "<<server_index<<endl;
	return file_id;
}

std::string DistributedStorage::localPut_with_fileid(std::string created_time, int size, std::string path_name, std::string file_type, std::string file_from, std::string row, std::string col, std::string data){
	table.lock_row(row);
	std::string file_id = table.put_with_fileid(created_time, size, path_name, file_type, file_from, row, col, data);
	cout<<"self id is "<<server_index<<" is_primary"<<is_primary<<" called by primary "<<primary_index<<endl;
	table.unlock_row(row);
	return file_id;
}

bool DistributedStorage::localCPut(std::string new_created_time, int new_size, std::string path_name, std::string file_type, std::string row, std::string col, std::string old_data, std::string new_data){
	if(!is_primary){
		table.lock_row(row);
	}
	bool res = table.cput(new_created_time, new_size, path_name, file_type, row, col, old_data, new_data);
	cout<<"self id is "<<server_index<<" calling localCPut"<<endl;
	if(!is_primary){
		table.unlock_row(row);
	}
	return res;
}

bool DistributedStorage::localDelete(string row, string col, string file_type, string path_name){
	if(!is_primary){
		table.lock_row(row);
	}
	bool res = table.table_delete(row, col, file_type, path_name);
	cout<<"self id is "<<server_index<<" calling localDelete"<<endl;
	if(!is_primary){
		table.unlock_row(row);
	}
	return res;
}

bool DistributedStorage::localRenameFifo(string row, string file_type, string path_name, string new_file_name){
	if(!is_primary){
		table.lock_row(row);
	}
	bool res = table.rename_file_folder(row, file_type, path_name, new_file_name);
	cout<<"self id is "<<server_index<<" calling localRenameFifo"<<endl;
	if(!is_primary){
		table.unlock_row(row);
	}
	return res;
}

bool DistributedStorage::localMoveFifo(string row, string file_type, string path_name, string new_path){
	if(!is_primary){
		table.lock_row(row);
	}
	bool res = table.move_file_folder(row, file_type, path_name, new_path);
	cout<<"self id is "<<server_index<<" calling localMoveFifo"<<endl;
	if(!is_primary){
		table.unlock_row(row);
	}
	return res;
}
