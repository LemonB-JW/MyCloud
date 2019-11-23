#include "../lib/MetaTree.h"
#include <iostream>


using namespace std;


vector<string> parse_filepath(string path_name){
	vector<string> file_list;
	size_t start_pos = 0;
	size_t end_pos = 0;
	
	while(start_pos < path_name.length() && end_pos != string::npos){
		end_pos = path_name.find("/", start_pos);
		string curr_name = path_name.substr(start_pos, end_pos-start_pos);
		// cout<<"file parse name is "<<curr_name<<endl;
		file_list.push_back(curr_name);
		start_pos = end_pos + 1;
	}
	return file_list;
}

void MetaTree::insertNode(string path_name, FileMetaData metadata){
	// split "root -> root/helper -> root/helper/dir/foo.txt"
	MetaTreeNode* node = root;
	vector<string> all_file_names = parse_filepath(path_name);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0){
			// cout<<"inserting file name is "<<curr_file_name<<endl;
			MetaTreeNode* new_node = new MetaTreeNode(curr_file_name, metadata);
			node->children[curr_file_name] = new_node;
			node = new_node;	
			// cout<<"new node is "<<node->file_name<<endl;
		}else{
			node = node->children[curr_file_name];
		}
	}
	node->is_leaf = true;
}

void MetaTree::insertNode(string path_name, MetaTreeNode* treenode){
	// split "root/helper/dir/foo.txt"
	MetaTreeNode* node = root;
	vector<string> all_file_names = parse_filepath(path_name);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0){

			node->children[curr_file_name] = treenode;
			node = treenode;
		}else{
			node = node->children[curr_file_name];
		}
	}
	
}

vector<MetaTreeNode*> MetaTree::searchNode(string path_name){
	// root/lib : foo.txt boo.txt
	MetaTreeNode* node = root;
	vector<MetaTreeNode*> res;
	vector<string> all_file_names = parse_filepath(path_name);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0) return res;
		else{
			node = node->children[curr_file_name];
		}
	}

	// cout<<"search node children size is "<<node->file_name<<"  "<<node->children.size()<<endl;
	res.push_back(node); // if it's a file, it only has on entry in the vector
	// it's a folder
	if(!node->children.empty()){
		for(auto it = node->children.begin(); it != node->children.end(); ++it){
			res.push_back(it->second);
		}
	}
	return res;
}

// true_delete is true when we want to delete the entire node, false when we want to re-insert the node
MetaTreeNode* MetaTree::deleteNode(string path_name, bool true_delete){
	// cout<<"Inside delete "<<endl;
	MetaTreeNode* node = root;
	MetaTreeNode* parent_node = root;
	string last_level_file_name = "";
	vector<string> all_file_names = parse_filepath(path_name);
	// root/lib   /foo.txt
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0) return NULL;
		else{
			parent_node = node;
			node = node->children[curr_file_name];
			last_level_file_name = curr_file_name;
		}
	}

	// cout<<"last_level_file_name is "<<last_level_file_name<<"  parent node is "<<parent_node->file_name<<" parent children size is "<<parent_node->children.size()<<endl;
	parent_node->children.erase(last_level_file_name);
	// cout<<"after erase in parent node, children size is "<<parent_node->children.size()<<endl;

	if(true_delete){
		
		// it's a folder
		if(!node->children.empty()){
			for(auto it = node->children.begin(); it != node->children.end(); ++it){
				// delete it->second;
				node->children.erase(it->first);
			}
		}
		// delete node;	
		// cout<<"exiting delete.."<<endl;
		return NULL;
	}else{
		// cout<<"else exiting delete.."<<endl;
		return node;
	}
	
}