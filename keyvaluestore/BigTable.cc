// Author: Jiaying Guo
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <unordered_map> 
#include "../lib/BigTable.h"
#include "../lib/Utility.h"

using namespace std;

// PUT(r,c,v): Stores a value v in column c of row r, if it's a folder, data should be "NULL"
bool BigTable::put(string created_time, int size, string path_name, string file_type, string file_from, string row, string data){ // col is the file_id generated in server side
	// write to big table
	string col = Utility::generateFileID(path_name);
	string file_name = Utility::parseFileName(path_name);
	if (table.count(row) == 0 || table.count(col) == 0) {
		string* data_pointer = new string(data);
		TableCell* new_cell = new TableCell(data_pointer);
		table[row][col] = new_cell;
		if(file_type == "email"){
			if(all_user_emails.count(row) == 0){
				all_user_emails[row] = new vector<FileMetaData*>();
			}
			// path_name for email as the file_name:
	 		FileMetaData* file_metadata = new FileMetaData(created_time, size, path_name, file_type, file_from, col);
			all_user_emails[row]->push_back(file_metadata);
		}else{
			if(all_user_files.count(row) == 0){
				all_user_files[row] = new MetaTree();
			}
			FileMetaData file_metadata(created_time, size, file_name, file_type, file_from, col);
			all_user_files[row]->insertNode(file_name, file_metadata);
		}
		
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

// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1, doesn't support folder
bool BigTable::cput(string new_created_time, int new_size, string path_name, string row, string col, string old_data, string new_data){
	if (table.count(row) == 0 || table[row].count(col) == 0){
		return false;
	}else{
		cout<<"else branch in cput.."<<endl;
		TableCell* cell = table[row][col];
		if (table[row][col]->contents->compare(old_data) == 0) {
			cell->contents = new string(new_data);
			// update file metadata
			if(file_type == "email"){
				for(int i = 0; i < all_user_emails[row]->size(); i++){
					if((all_user_emails[row]->at(i)->file_id).compare(col) == 0){
						all_user_emails[row]->at(i)->created_time = new_created_time;
						all_user_emails[row]->at(i)->size = new_size;
					}
				}	
			}else if(file_type == "file"){
				string file_name = Utility::parseFileName(path_name);
				vector<MetaTreeNode*> node = all_user_files[row]->searchNode(file_name)
				node.at(0)->created_time = new_created_time;
				node.at(0)->size = new_size;
			}
			return true;
		} 
	}
	return false;
}

// DELETE(r,c): Deletes the value in column c of row r
bool BigTable::table_delete(string row, string col, string file_type, string path_name){
	if (table.count(row) == 0 || table[row].count(col) == 0) {
		return false;
	}else{
		table[row].erase(col);
		// delete metadata from management:
		if(file_type == "email"){
			for(int i = 0; i < all_user_emails[row]->size(); i++){
				if((all_user_emails[row]->at(i)->file_id).compare(col) == 0){
					all_user_emails[row]->erase(all_user_emails[row]->begin() + i - 1);
				}
			}
		}else{
			//it's a file or folder:
			all_user_files[row]->deleteNode(path_name, true);
		}

		return true;
	}
}

// only list emails
vector<FileMetaData> BigTable::list_all_emails_for_currUser(string row){
	vector<FileMetaData> result;
	for(auto itr = all_user_emails[row]->begin(); itr !=  all_user_emails[row]->end(); itr++){
		FileMetaData* file = *itr;
		if((file->file_type).compare("email") == 0){
			FileMetaData file_info(file->created_time, file->size, file->file_name, file->file_type, file->file_from, file->file_id);
			// string file_info = FileMetaData::metaDataToString(file);
			result.push_back(file_info);
		}
	}
	return result;
}

// Return a list of file/folder metadata of given path:
vector<FileMetaData> BigTable::list_all_files_for_currUser(string row, string path_name){
	vector<MetaTreeNode*> nodes = all_user_files[row]->searchNode(path_name);
	vector<FileMetaData> result;
	for(int i = 0; i < nodes.size(); i++){
		FileMetaData file_info(nodes.at(i)->metadata->created_time, nodes.at(i)->metadata->size, nodes.at(i)->metadata->file_name, nodes.at(i)->metadata->file_type, nodes.at(i)->metadata->file_from, nodes.at(i)->metadata->file_id);
		result.push_back(file_info);
	}
	return result;
}


bool BigTable::rename_file_folder(string row, string file_type, string path_name, string new_file_name){
	vector<MetaTreeNode*> nodes = all_user_files[row]->searchNode(path_name);
	if(nodes == NULL) return false;
	nodes.at(0)->file_name = new_file_name;
	return true;
}

bool BigTable::move_file_folder(string row, string file_type, string path_name, string new_path){
	MetaTreeNode* node = all_user_files[row]->deleteNode(path_name, false);
	if(node == NULL) return false;
	all_user_files[row]->insertNode(new_path, node);
	return true;
}

