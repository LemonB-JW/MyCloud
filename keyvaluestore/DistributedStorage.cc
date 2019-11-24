#include "../lib/DistributedStorage.h"
#include <sys/file.h>
#include <iostream>
#include <iterator>
using namespace std;

/* Construct an address information struct from a given full IP address */
struct addr_info DistributedStorage::constructAddrInfo(string ip_port){
  size_t found_colon = ip_port.find(":");
  if(found_colon == string::npos){
    throw "Invalid input server address!";
  }
  struct addr_info info;
  info.ip = ip_port.substr(0, found_colon);
  info.port = atoi((ip_port.substr(found_colon + 1)).c_str());
  return info;
}

void DistributedStorage::readConfigFile(const char* config_file, const char* server_id){
	 // read from config file, get the forward and bind address of current server and of all other servers
	  string f_name(config_file);
	  ifstream file(config_file);
	  cout<<"server id is "<<config_file<<" "<<server_id<<endl;
	  server_index = atoi(server_id);
	  cout<<"server index is "<<server_index<<endl;
	  if(file.fail()){
	    fprintf(stderr, "Cannot open config file.\n");
	    exit(1);
	  }
	  string line;
	  while(getline(file, line)){
	    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
	    line.erase(remove(line.begin(), line.end(), '\r'), line.end());
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
	  self_addr.ip = all_server_back_addr.at(server_index - 1).ip;
	  self_addr.port = all_server_back_addr.at(server_index - 1).port;
	  cout<<"num of servers is "<<num_of_servers<<endl;
	  if(num_of_servers < server_index){
	    fprintf(stderr, "%s\n", "Current file doesn't support your input index!");
	    // cleanup();
	    exit(1);
	  }
}

void DistributedStorage::parseAllSubIndices(vector<int> all_sub_indices){
	for(int i = 0; i < all_sub_indices.size(); i++){
		all_sub_addr.push_back(all_server_back_addr.at(all_sub_indices.at(i)));
	}
}

void DistributedStorage::updatePrimary(int primary_index){
	if(primary_index == server_index) is_primary = true;
	addr_info* primary_addr = new addr_info();
	primary_addr->ip = all_server_back_addr.at(primary_index).ip;
	primary_addr->port = all_server_back_addr.at(primary_index).port;
}

// bool DistributedStorage::localPut(string created_time, int size, string path_name, string file_type, string file_from, string row, string data){

// 	string file_id = table.put(created_time, size, path_name, file_type, file_from, row, data);
// 	return true;
// }

string DistributedStorage::localPut(string created_time, int size, string path_name, string file_type, string file_from, string row, string data){
	string file_id = table.put(created_time, size, path_name, file_type, file_from, row, data);
	return file_id;
}

string DistributedStorage::localPut_with_fileid(string created_time, int size, string path_name, string file_type, string file_from, string row, string col, string data){
	string file_id = table.put_with_fileid(created_time, size, path_name, file_type, file_from, row, col, data);
	return file_id;
}
