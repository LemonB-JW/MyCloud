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

void BigTable::lock_row(string row){
	pthread_mutex_lock(&table_lock);
	cout<<"enter bigtable lock_row.."<<endl;
	if(table.count(row) == 0){
		unordered_map<string, TableCell*> values;
		table[row] = values;
		all_user_locks[row] = new pthread_mutex_t();
		pthread_mutex_init(all_user_locks[row], NULL);
	}
	pthread_mutex_unlock(&table_lock);
	pthread_mutex_lock(all_user_locks[row]);
}

void BigTable::unlock_row(string row){
	cout<<"enter bigtable unlock_row.."<<endl;
	pthread_mutex_unlock(all_user_locks[row]);
}

// PUT(r,c,v): Stores a value v in column c of row r, if it's a folder, data should be "NULL"
string BigTable::put(string created_time, int size, string path_name, string file_type, string file_from, string row, string data){ // col is the file_id generated in server side
	// write to big table
	string res = "";
	if(all_user_files.count(row) != 0){
		vector<MetaTreeNode*> search_results = all_user_files[row]->searchNode(path_name);
		if(search_results.size() > 0){
			return res;
		}
	}
	cout<<"finish searching the node"<<endl;
	string col = Utility::generateFileID(path_name);
	// cout<<"row is "<<row<<" generated file id is "<<col<<endl;
	string file_name = Utility::parseFileName(path_name);
	cout<<"in big table put, parsed file name is "<<file_name<<endl;
	if (table.count(row) == 0 || table[row].count(col) == 0 ) {
		res = col;
		string* data_pointer = new string(data);
		TableCell* new_cell = new TableCell(data_pointer);
		table[row][col] = new_cell;
		cout<<"put content is "<<(*(table[row][col]->contents))<<endl;
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
			// cout<<"before insert node"<<endl;
			FileMetaData file_metadata(created_time, size, file_name, file_type, file_from, col);
			all_user_files[row]->insertNode(path_name, file_metadata);
		}
		
	}
	return res;
}



// PUT(r,c,v): Stores a value v in column c of row r, if it's a folder, data should be "NULL"
string BigTable::put_with_fileid(string created_time, int size, string path_name, string file_type, string file_from, string row, string col, string data){ // col is the file_id generated in server side
	// write to big table
	string res = "";
	// cout<<"row is "<<row<<" generated file id is "<<col<<endl;
	string file_name = Utility::parseFileName(path_name);
	if (table.count(row) == 0 || table.count(col) == 0) {
		res = col;
		string* data_pointer = new string(data);
		TableCell* new_cell = new TableCell(data_pointer);
		table[row][col] = new_cell;
		cout<<"put content is "<<(*(table[row][col]->contents))<<endl;
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
			// cout<<"before insert node"<<endl;
			FileMetaData file_metadata(created_time, size, file_name, file_type, file_from, col);
			all_user_files[row]->insertNode(path_name, file_metadata);
		}
		
	}else{
		return "";
	}

	return res;
}


// GET(r,c): Returns the value stored in column c of row r
string BigTable::get(string row, string col) {
	// cout<<"row, col "<<row<<" "<<col<<endl;
	if (table.count(row) == 0) {
		return "";
	}else{
		if(table[row].count(col) == 0){
			return "";
		}else{
			string res = *(table[row][col]->contents);
			return res;			
		}
	}
}

// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1, doesn't support folder
bool BigTable::cput(string new_created_time, int new_size, string path_name, string file_type, string row, string col, string old_data, string new_data){
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
				vector<MetaTreeNode*> node = all_user_files[row]->searchNode(file_name);
				node.at(0)->metadata->created_time = new_created_time;
				node.at(0)->metadata->size = new_size;
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
vector<FileMetaData> BigTable::list_all_emails(string row){
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

// Return a list of file/folder metadata of given path: only pass in folder path not file name!
vector<FileMetaData> BigTable::list_all_files(string row, string path_name){
	vector<MetaTreeNode*> nodes = all_user_files[row]->searchNode(path_name);
	vector<FileMetaData> result;
	for(int i = 2; i < nodes.size(); i++){
		FileMetaData file_info(nodes.at(i)->metadata->created_time, nodes.at(i)->metadata->size, nodes.at(i)->metadata->file_name, nodes.at(i)->metadata->file_type, nodes.at(i)->metadata->file_from, nodes.at(i)->metadata->file_id);
		cout<<"list all files file name is "<<file_info.file_name<<endl;
		result.push_back(file_info);
	}
	return result;
}


bool BigTable::rename_file_folder(string row, string file_type, string path_name, string new_file_name){
	string file_name = Utility::parseFileName(new_file_name);
	cout<<"rename folder/file new name "<<new_file_name<<endl;
	vector<MetaTreeNode*> nodes = all_user_files[row]->searchNode(path_name);
	if(nodes.empty()) return false;
	cout<<"rename came back from searchNode"<<" nodes size is "<<nodes.size()<<endl;
	string ori_filename = nodes.at(1)->file_name;
	MetaTreeNode* temp;
	for(auto it = nodes.at(0)->children.begin(); it != nodes.at(0)->children.end(); ++it){
		cout<<"children name is "<<it->first<<endl;
		if(it->first.compare(ori_filename) == 0){
			cout<<"renaming .."<<endl;
			it->second->file_name = file_name;
			temp = it->second;
			nodes.at(0)->children.erase(it->first);
			break;
		}
	}

	cout<<"out of for loop"<<endl;
	nodes.at(1)->file_name = file_name;
	nodes.at(1)->metadata->file_name = file_name;
	nodes.at(0)->children[file_name] = temp;
	cout<<"new child size "<<nodes.at(0)->children[file_name]->children.size()<<endl;
	return true;
}

bool BigTable::move_file_folder(string row, string file_type, string path_name, string new_path){
	MetaTreeNode* node = all_user_files[row]->deleteNode(path_name, false);
	cout<<"finished deleting in move_file_folder.."<<endl;
	if(node == NULL) return false;
	all_user_files[row]->insertNode(new_path, node);
	cout<<"finished inserting in move_file_folder.."<<endl;
	return true;
}

