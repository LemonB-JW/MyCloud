#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "FileData.h"


using namespace std;

/* 3 Methods for check pointing and sending to front-end servers*/

string FileData::metaDataToString(const FileData* file_data){
	bool is_file = file_data->is_file;
	string created_time = file_data->created_time;
	int size = file_data->size; // num of bytes of that file
	string file_name = file_data->file_name;
	string file_id = file_data->file_id; // created_time + file_name

	string result = "";

	if(is_file){
		result = "fi:" + created_time + file_name + file_id + to_string(size);
	}else{
		result = "fo:" + created_time + file_name + file_id + to_string(size);
	}
	return result;

}
 
// string FileData::contentToString(const FileData* file_data){
// 	vector<char>* content = file_data->content;
// 	string result = "";
// 	for(int i = 0; i < content->size(); i++){
// 		string curr(content->at(i));
// 		result += curr;
// 	}
// 	return result;
// }

