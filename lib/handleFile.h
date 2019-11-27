/*
	Author: Peng Li
	11/25/2019
*/

#ifndef HANDLEFILE_H_
#define HANDLEFILE_H_

//#include <stdio.h>
#include <string>

bool existFile(const std::string& filepath);
bool readFile(const std::string& filepath, std::string& content);
bool writeFile(const std::string& filepath, const std::string& content);
bool appendFile(const std::string& filepath, const std::string& content);
bool deleteFile(const std::string& filepath);
bool renameFile(const std::string& old_filepath, const std::string& new_filepath);

#endif /* HANDLEFILE_H_ */
