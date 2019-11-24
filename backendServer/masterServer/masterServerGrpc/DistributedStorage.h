#include <iostream>
#include <vector>
#include <string.h>
#include <stdbool.h>
using namespace std;

/* struct for storing IP address information */
typedef struct addr_info{
  string ip;
  int port;
}addr_info;


class DistributedStorage
{

private:
	vector<addr_info> all_server_front_addr;
	vector<addr_info> all_server_back_addr
	int server_index = 0, num_of_servers = 0;
	addr_info self_addr;
	bool is_primary = false;
	vector<addr_info> all_sub_addr;
	addr_info master_addr;
	addr_info* primary_addr;
	struct addr_info constructAddrInfo(string ip_port);


public:
	BigTable table;
	DistributedStorage();
	~DistributedStorage();
	

	void readConfigFile(string config_file, string server_index);
	void parseAllSubIndices(vector<int> all_sub_indices);
	void updatePrimary(int primary_index);
	string file_id localPut_with_fileid(string created_time, int size, string path_name, string file_type, string file_from, string row, string col, string data);
	string file_id localPut(string created_time, int size, string path_name, string file_type, string file_from, string row, string col, string data);


};