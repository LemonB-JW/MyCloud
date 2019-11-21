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
#include "../lib/FileMetaData.h"


using namespace std;

class BigTable
{
public:
	unordered_map<string, unordered_map<string, TableCell*>> table; // row key: user name, col key: fileID (every folder has a unique ID: workerIndex + sequenceNum + timestamp
	unordered_map<string, vector<FileMetaData*>*> all_user_files;
	BigTable(){
	};
	~BigTable(){
	}

	// PUT(r,c,v): Stores a value v in column c of row r
	bool put(string created_time, int size, string file_name, string file_type, string row, string col, string data);

	// GET(r,c): Returns the value stored in column c of row r
	string get(string row, string col);

	// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1
	bool cput(string created_time, int size, string file_name, string file_type, string row, string col, string old_data, string new_data);

	// DELETE(r,c): Deletes the value in column c of row r
	bool table_delete(string row, string col);

	vector<string> list_all_files_for_currUser(string row);
	vector<string> list_all_emails_for_currUser(string row);

};

#endif