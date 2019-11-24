#include "../lib/BigTable.h"
#include <iostream>
#include <string.h>
#include <stdbool.h> 
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	
	BigTable table;
	string data = "Welcome to penn cloud!\n";
	string new_data = "Bye\n";
	// string id1 = Utility::generateFileID(2, 1);
	string id1 = "foo.txt";
	// cout<<"id1 is "<<id1<<endl;
	// cout<<"put1"<<endl;
	string fileID1 = table.put("2019/11/20", 0, "root", "folder", "alice", "janice", "NULL");

	string val = table.get("janice", fileID1);
	// cout<<"get val "<<val<<endl;
	// table.table_delete("janice", fileID1, "file", "root/lib/foo.txt");
	//bool ret2 = table.cput("2019/11/20", 97, "root/lib/foo.txt", "file", "alice", "janice", id1, data, new_data);
	
	
	// cout<<"put return val is "<<ret<<"cput ret is "<<ret2<<endl;
	
	string fileID3 = table.put("2019/11/20", 0, "root/lib", "folder", "alice", "janice", "NULL");
	string fileID2 = table.put("2019/11/20", 20, "root/lib/boo.txt", "file", "alice", "janice", "Welcome\n");
	string fileID4 = table.put("2019/11/20", 10, "root/lib/foo.txt", "file", "alice", "janice", "Hellooo\n");
	cout<<"to delete.."<<endl;
	// table.table_delete("janice", fileID3, "folder","root/lib");
	
	table.rename_file_folder("janice", "folder", "root/lib", "usr");
	table.move_file_folder("janice","file", "root/usr/foo.txt", "root/foo.txt");
	// cout<<"all files size is "<<all_files.size();
	vector<FileMetaData> all_files = table.list_all_files("janice","root/usr");
	if(all_files.empty()) cout<<"not exist folder / file.."<<endl;
	else{
		for(int i = 0; i < all_files.size(); i++){
			cout<<"file name is "<<all_files.at(i).file_name<<endl;
			cout<<"file content is "<<table.get("janice", all_files.at(i).file_id)<<endl;
		}
	}
	

	return 0;
}