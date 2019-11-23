// Author: Jiaying Guo
#include "../lib/MetaTreeNode.h"
#include <vector>
#include <string.h>

using namespace std;

class MetaTree
{
public:
	MetaTreeNode* root;

	MetaTree(){
		FileMetaData data;
		root = new MetaTreeNode("root", data);
	}
	~MetaTree(){
		delete root;
	};
	
public:
	void insertNode(string path_name, FileMetaData metadata);
	void insertNode(string path_name, MetaTreeNode* treenode);
  	MetaTreeNode* deleteNode(string path_name, bool true_delete);
   	vector<MetaTreeNode*> searchNode(string path_name);



};