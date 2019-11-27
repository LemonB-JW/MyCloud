#include <stdio.h>//FILE type
#include "../lib/handleFile.h"

bool existFile(const std::string& filepath){
	FILE* fp = fopen(filepath.c_str(), "r");
	if (!fp) {
		return false;
	}
	fclose(fp);
	return true;
}

bool readFile(const std::string& filepath, std::string& content){
	FILE* fp = fopen(filepath.c_str(), "r");
	if (!fp) {
		return false;
	}
	fseek(fp, 0, SEEK_END);
	size_t fileSize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* charContent = (char*)malloc(sizeof(char)*fileSize);
	fread(charContent, sizeof(char), fileSize, fp);
	fclose(fp);
	content = charContent;
	delete[] charContent;
	return true;
}

bool writeFile(const std::string& filepath, const std::string& content){
	FILE* fp = fopen(filepath.c_str(), "w");
	if (!fp) {
		return false;
	}
	fwrite(content.c_str(), sizeof(char), content.size(), fp);
	fclose(fp);
	return true;
}

bool appendFile(const std::string& filepath, const std::string& content){
	FILE* fp = fopen(filepath.c_str(), "a");
	if (!fp) {
		return false;
	}
	fwrite(content.c_str(), sizeof(char), content.size(), fp);
	fclose(fp);
}

bool deleteFile(const std::string& filepath){
	if (remove(filepath.c_str()) < 0) return false;
	else return true;
}

bool renameFile(const std::string& old_filepath, const std::string& new_filepath){
	if (rename(old_filepath.c_str(), new_filepath.c_str()) <0) return false;
	else return true;
}



