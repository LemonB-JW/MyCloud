// Author: Jiaying Guo

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "../lib/FileMetaData.h"


using namespace std;

/* 3 Methods for check pointing and sending to front-end servers*/

string FileMetaData::metaDataToString(const FileMetaData* file_data){
	string file_type = file_data->file_type;
	string created_time = file_data->created_time;
	int size = file_data->size; // num of bytes of that file
	string file_name = file_data->file_name;
	string file_id = file_data->file_id; // created_time + file_name

	string result = "";
	result = file_type + "," + created_time + "," + file_name + "," + file_id + "," + to_string(size);
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

