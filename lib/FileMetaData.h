#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
using namespace std;

class FileData
{
public:
	string created_time;
	int size; // num of bytes of that file
	string file_name;
	bool is_file; // if it's a folder, its content should be NULL
	string file_id; // created_time + file_name
	// vector<char>* content;

public:
	FileData(string created_time, int size, string file_name, bool is_file, string file_id){ //, const char* content_bytes
		this->created_time = created_time;
		this->size = size;
		this->file_name = file_name;
		this->is_file = is_file;
		this->file_id = file_id;
		// this->content = new vector<char>();
		// for(int i = 0; i < strlen(content_bytes); i++){
		// 	this->content->push_back(content_bytes[i]);
		// }
	};
	~FileData(){
		//delete this->content;
	};

	/* Convert file meta data to string*/
 	string metaDataToString(const FileData* file_data);
 	/* Convert file content to string */
 	string contentToString(const FileData* file_data); 	

};

