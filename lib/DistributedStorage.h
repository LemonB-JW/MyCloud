#include <string.h>
// #include <openssl/md5.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <unistd.h>
#include <iostream>
#include <ctype.h>
#include <vector>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <bits/stdc++.h> 
#include <sys/file.h>
#include <iterator> 
#include "../lib/BigTable.h"

using namespace std;
typedef struct addr_info{
  string ip;
  int port;
}addr_info;

class DistributedStorage
{
	
public:
	int server_index = 0, num_of_servers = 0, primary_index = 0;
	bool is_primary = false; 
	vector<addr_info> all_server_front_addr;
	vector<addr_info> all_server_back_addr;
	addr_info master_addr, self_addr;
	addr_info* primary_addr;
	vector<addr_info> all_sub_addr;
	BigTable table;
	unordered_map<string, pthread_mutex_t*> all_user_locks; // key: user, val: lock
	// DistributedStorage();
	~DistributedStorage();

	struct addr_info constructAddrInfo(string ip_port);
	void readConfigFile(const char* config_file, const char* server_index);
	void parseAllSubIndices(vector<int> all_sub_indices);
	void updatePrimary(int primary_index);
	string localPut(string created_time, int size, string path_name, string file_type, string file_from, string row, string data);
	string localPut_with_fileid(string created_time, int size, string path_name, string file_type, string file_from, string row, string col, string data);
	bool localCPut(string new_created_time, int new_size, string path_name, string file_type, string row, string col, string old_data, string new_data);
	bool localDelete(string row, string col, string file_type, string path_name);
	bool localRenameFifo(string row, string file_type, string path_name, string new_file_name);
	bool localMoveFifo(string row, string file_type, string path_name, string new_path);
};