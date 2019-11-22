#include "../lib/MetaTree.h"
#include <iostream>
#include <iterator>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split


using namespace std;


void MetaTree::insertNode(string path_name, FileMetaData metadata){
	// split "root/helper/dir/foo.txt"
	MetaTreeNode* node = root;
	vector<string> all_file_names;
	boost::split(all_file_names, ,path_name boost::is_any_of("/"), boost::token_compress_on);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0){
			MetaTreeNode* new_node = new MetaTreeNode(curr_file_name, metadata);
			node->children[curr_file_name] = new_node;
			node = new_node;
		}else{
			node = node->children[curr_file_name];
		}
	}
	node->is_leaf = true;
}

void MetaTree::insertNode(string path_name, MetaTreeNode* treenode){
	// split "root/helper/dir/foo.txt"
	MetaTreeNode* node = root;
	vector<string> all_file_names;
	boost::split(all_file_names, ,path_name boost::is_any_of("/"), boost::token_compress_on);
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
	MetaTreeNode* node = root;
	vector<string> all_file_names;
	boost::split(all_file_names, ,path_name boost::is_any_of("/"), boost::token_compress_on);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0) return NULL;
		else{
			node = node->children[curr_file_name];
		}
	}

	vector<MetaTreeNode*> res;
	res.push_back(node); // if it's a file, it only has on entry in the vector
	// it's a folder
	if(node->children != NULL){
		for(auto it = node->children.begin(); it != node->children.end(); ++it){
			res.push_back(it->second);
		}
	}
	return res;
}

// true_delete is true when we want to delete the entire node, false when we want to re-insert the node
MetaTreeNode* MetaTree::deleteNode(string path_name, bool true_delete){
	MetaTreeNode* node = root;
	MetaTreeNode* parent_node = root;
	vector<string> all_file_names;
	string last_level_file_name = "";
	boost::split(all_file_names, ,path_name boost::is_any_of("/"), boost::token_compress_on);
	for(int i = 0; i < all_file_names.size(); i++){
		string curr_file_name = all_file_names.at(i);
		if(node->children.count(curr_file_name) == 0) return NULL;
		else{
			parent_node = node;
			node = node->children[curr_file_name];
			last_level_file_name = curr_file_name;
		}
	}
	parent_node->children.erase(last_level_file_name);
	
	if(true_delete){
		// it's a folder
		if(node->children != NULL){
			for(auto it = node->children.begin(); it != node->children.end(); ++it){
				node->children.erase(it->first);
			}
		}	
		return NULL;
	}else{
		return node;
	}
	
}