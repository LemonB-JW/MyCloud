// Author: Jiaying Guo

#ifndef BIGTABLE_H_ 
#define BIGTABLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <unordered_map> 
#include <stdbool.h> 
#include "../lib/TableCell.h"
#include "../lib/MetaTree.h"


using namespace std;

class BigTable
{
public:
	 // row key: user name, col key: fileID = timestamp + fullpath
	unordered_map<string, unordered_map<string, TableCell*>> table;
	unordered_map<string, vector<FileMetaData*>*> all_user_emails;
	unordered_map<string, MetaTree*> all_user_files;
	// BigTable();
	~BigTable(){
		for(auto it = table.begin(); it != table.end();++it){
			table.erase(it->first);
		}

		for(auto it = all_user_emails.begin(); it != all_user_emails.end();++it){
			// delete it->second;
			all_user_emails.erase(it->first);
		}

		for(auto it = all_user_files.begin(); it != all_user_files.end();++it){
			
			// delete it->second;
			all_user_files.erase(it->first);
		}

	};

	/*PUT: generate a fileID based on timestamp and path_name, which will be returned after the method is called.
	*** if the file cannot be put into table, it will return "" (empty string). ***
	row: username, (email) receiver/owner, created_time: file created time, file_type: "email", "folder", "file"
	path_name: (email) email subject name, (file/folder): PATH/file or folder name
	size: number of bytes of the file, it should be 0 when file type is "folder", file_from: (email) sender username, (file) "NULL" 
	data: file data, it should be "NULL" when the file type is "folder"
	*** the management structures: tree for file system, map for email system will be updated as well ***
	*/
	string put(string created_time, int size, string path_name, string file_type, string file_from, string row, string data); // col is the file_id generated in server side

	/* GET: row: username, col: fileID, return the content of the file */
	string get(string row, string col);

	/* CPUT: row: username, (email) receiver/owner, new_created_time: file modified time
	path_name: (email) email subject name, (file/folder): PATH/file or folder name
	new_size: number of bytes of the modified file, old_data: original file data
	new_data: modified file data
	*** the management structures: tree for file system, map for email system will be updated as well ***
	*/
	bool cput(string new_created_time, int new_size, string path_name, string file_type, string row, string col, string old_data, string new_data);

	/* DELETE: row: username, (email) receiver/owner, col: fileID
	path_name: (email) email subject name, (file/folder): PATH/file or folder name
	file_type: "email", "folder", "file"
	*** the management structures: tree for file system, map for email system will be updated as well ***
	*/
	bool table_delete(string row, string col, string file_type, string path_name);

	/* return a list of all file/folder metadata under a given path of a user (row) */
	vector<FileMetaData> list_all_files(string row, string path_name);

	/* return a list of all emails metadata of a user (row) */
	vector<FileMetaData> list_all_emails(string row);

	/* only for file system:
	   row: user, file_type: "email", "folder", "file", path_name: (email) email subject name, (file/folder): PATH/file or folder name
	   new_file_name: PATH/newfilename
	   *** the management structures: tree for file system will be updated as well ***
	 */
	bool rename_file_folder(string row, string file_type, string path_name, string new_file_name);

	/* only for file system:
	   row: user, file_type: "email", "folder", "file", path_name: (email) email subject name, (file/folder): PATH/file or folder name
	   new_path: PATH/newfilename
	   *** the management structures: tree for file system will be updated as well ***
	*/
	bool move_file_folder(string row, string file_type, string path_name, string new_path);



};

#endif