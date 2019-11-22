// Author: Jiaying Guo
#include "../lib/FileMetaData.h"
#include <vector.h>
#include <string.h>
#include <unordered_map>
#include <stdbool.h>

using namespace std;

class MetaTreeNode
{

public:
	string filename;
	FileMetaData* metadata;
	unordered_map<string, MetaTreeNode*> children; // key: file_name, value: metadata node
	bool is_leaf;

	MetaTreeNode(string file_name, FileMetaData metadata){
		this->filename = file_name;
		FileMetaData* mdata = new FileMetaData(metadata.created_time, metadata.size, metadata.file_name, metadata.file_type, metadata.file_from, metadata.file_id);
		this->metadata = mdata;
	};
	~MetaTreeNode(){
		for(int i = 0; i < children.size(); i++){
			children.erase(children.begin() + i - 1);
		}
	};

};