#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <unordered_map> 
#include "../lib/TableCell.h"

using namespace std;

class BigTable
{
public:
	unordered_map<string, unordered_map<string, TableCell*>> table; // row key: user name, col key: fileID (every folder has a unique ID: workerIndex + sequenceNum + timestamp
	// unordered_map<string, FileData*> files_in_path;
	BigTable(){
	};
	~BigTable(){
	}

	// PUT(r,c,v): Stores a value v in column c of row r
	bool put(string row, string col, string* data);

	// GET(r,c): Returns the value stored in column c of row r
	string get(string row, string col);

	// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1
	bool cput(string row, string col, string* old_data, string* new_data);

	// DELETE(r,c): Deletes the value in column c of row r
	bool table_delete(string row, string col);

};