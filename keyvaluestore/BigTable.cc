// Author: Jiaying Guo


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <unordered_map> 
#include "../lib/BigTable.h"

using namespace std;

// PUT(r,c,v): Stores a value v in column c of row r
bool BigTable::put(string created_time, int size, string file_name, string file_type, string row, string col, string data){ // col is the file_id generated in server side
	// write to big table

	if (table.count(row) == 0 || table.count(col) == 0) {
		string* data_pointer = new string(data);
		TableCell* new_cell = new TableCell(data_pointer);
		table[row][col] = new_cell;
		if(all_user_files.count(row) == 0){
			all_user_files[row] = new vector<FileMetaData*>();
			// cout<<"init all user files..."<<endl;
		}
 		FileMetaData* file_metadata = new FileMetaData(created_time, size, file_name, file_type, col);
		all_user_files[row]->push_back(file_metadata);
		// cout<<"curr user files number is "<<all_user_files[row]->at(0)->file_name<<endl;
	} else {
		return false;
	}

	return true;
}

// GET(r,c): Returns the value stored in column c of row r
string BigTable::get(string row, string col) {
	if (table.count(row) == 0) {
		return "";
	}else{
		if(table[row].count(col) == 0){
			return "";
		}else{
			return *(table[row][col]->contents);			
		}
	}
}

// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1
bool BigTable::cput(string created_time, int size, string file_name, string file_type, string row, string col, string old_data, string new_data){
	if (table.count(row) == 0 || table[row].count(col) == 0){
		cout<<"if branch in cput..."<<endl;
		if (old_data == "NULL") { // empty file
			string* data_pointer = new string(new_data);
			table[row][col] = new TableCell(data_pointer);
			// TableCell* new_cell = new TableCell(new_data);
			FileMetaData* file_metadata = new FileMetaData(created_time, size, file_name, file_type, col);
			all_user_files[row]->push_back(file_metadata);
			return true;
		} else {
			return false;
		}
		
	} else {
		cout<<"else branch in cput.."<<endl;
		TableCell* cell = table[row][col];
		if (table[row][col]->contents->compare(old_data) == 0) {
			cell->contents = new string(new_data);
			FileMetaData* new_file_metadata = new FileMetaData(created_time, size, file_name, file_type, col);
			for(int i = 0; i < all_user_files[row]->size(); i++){
				if((all_user_files[row]->at(i)->file_id).compare(col) == 0){
					all_user_files[row]->at(i) = new_file_metadata;
				}
			}	
			return true;
		} else {
			return false;
		}
	}
}

// DELETE(r,c): Deletes the value in column c of row r
bool BigTable::table_delete(string row, string col){
	if (table.count(row) == 0) {
		return false;
	}else{
		if(table[row].count(col) == 0){
			return false;
		} else {
			table[row].erase(col);
			for(int i = 0; i < all_user_files[row]->size(); i++){
				if((all_user_files[row]->at(i)->file_id).compare(col) == 0){
					all_user_files[row]->erase(all_user_files[row]->begin() + i - 1);
				}
			}
			return true;
		}
	}
}

// only list emails
vector<string> BigTable::list_all_emails_for_currUser(string row){
	vector<string> result;
	for(auto itr = all_user_files[row]->begin(); itr !=  all_user_files[row]->end(); itr++){
		FileMetaData* file = *itr;
		if((file->file_type).compare("email") == 0){
			string file_info = FileMetaData::metaDataToString(file);
			result.push_back(file_info);
		}
	}
	return result;
}

// skip email files, only contains folders and files
vector<string> BigTable::list_all_files_for_currUser(string row){
	cout<<"inside list_all_files_for_currUser.."<<"user is "<<row<<" number of user files is "<<all_user_files[row]->size()<<endl;
	vector<string> result;
	for(auto itr = all_user_files[row]->begin(); itr !=  all_user_files[row]->end(); itr++){
		FileMetaData* file = *itr;
		if((file->file_type).compare("email") != 0){
			string file_info = FileMetaData::metaDataToString(file);
			result.push_back(file_info);
		}
	}
	return result;
}