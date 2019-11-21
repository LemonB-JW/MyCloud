#include "../lib/BigTable.h"
#include "../lib/Utility.h"
#include <iostream>
#include <string.h>
#include <stdbool.h> 
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	
	BigTable table;
	string data = "Welcome\n";
	string new_data = "Bye\n";
	// string id1 = Utility::generateFileID(2, 1);
	string id1 = "foo.txt";
	// cout<<"id1 is "<<id1<<endl;
	bool ret = table.put("2019/11/20", 0, "foo.txt", "file", "alice", "janice", id1, data);
	string val = table.get("alice", "foo.txt");
	cout<<"get val "<<val<<endl;
	bool ret2 = table.cput("2019/11/20", 97, "foo.txt", "file", "alice", "janice", id1, data, new_data);
	
	
	// cout<<"put return val is "<<ret<<"cput ret is "<<ret2<<endl;
	table.table_delete("alice", "foo.txt");
	// string val2 = table.get("alice", "foo.txt");
	// cout<<"get new val "<<val2<<endl;
	string data2 = "boo welcome..\n";
	string id2 = Utility::generateFileID(2, 1);
	// string id2 = "boo.txt";
	// cout<<"id2 is "<<id2<<endl;
	bool ret3 = table.put("2019/11/20", 10, "boo.txt", "file", "alice", "janice",id2, data2);
	vector<FileMetaData> all_files = table.list_all_files_for_currUser("alice");
	for(int i = 0; i < all_files.size(); i++){
		cout<<"file info is "<<all_files.at(i).file_name<<endl;
	}
	return 0;
}