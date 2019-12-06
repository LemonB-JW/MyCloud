#ifndef FILEMETADATA_H
#define FILEMETADATA_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>

class FileMetaData
{
public:
	std::string created_time;
	int size; // num of bytes of that file
	std::string file_name;
	std::string file_type; // 3 types: "email", "folder", "file", if it's a folder, its content should be NULL
	std::string file_from;
	std::string file_id; // created_time + file_name
	// vector<char>* content;

public:
	FileMetaData(std::string created_time, int size, std::string file_name, std::string file_type, std::string file_from, std::string file_id){ //, const char* content_bytes
		this->created_time = created_time;
		this->size = size;
		this->file_name = file_name;
		this->file_type = file_type;
		this->file_from = file_from;
		this->file_id = file_id;
		// this->content = new vector<char>();
		// for(int i = 0; i < strlen(content_bytes); i++){
		// 	this->content->push_back(content_bytes[i]);
		// }
	};
	FileMetaData(){

	};
	~FileMetaData(){
		//delete this->content;
	};

	/* Convert file meta data to string*/
 	static std::string metaDataToString(const FileMetaData* file_data);
 	// /* Convert file content to string */
 	// string contentToString(const FileData* file_data); 	

};

#endif

