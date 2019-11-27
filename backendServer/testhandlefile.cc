/*
	Author: Peng Li
*/
#include <string>
#include <vector>
#include "handleFile.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif



int main(int argc, char** argv){
	if (argc < 2)
    panic("*** Final Project T08, Author: Peng Li (pl279)\n");
    
	std::vector<std::string> filevector;
	for (int i = 1; i < argc; i++){
		std::string temp;
		temp = argv[i];
		filevector.push_back(temp);
	}
	
	fprintf(stderr, "read all args into vector \n");
	
	for (int i = 0; i < filevector.size(); i++){
		
		if (existFile(filevector[i])){
			fprintf(stderr, "file %s exist\n", filevector[i].c_str());
			std::string contentinfile;
			readFile(filevector[i], contentinfile);
			fprintf(stderr, "file content is '%s'\n", contentinfile.c_str());
			
		}else{
			fprintf(stderr, "file %s does not exist\n", filevector[i].c_str());
			std::string contentinfile = "write into new file";
			writeFile(filevector[i], contentinfile);
			fprintf(stderr, "read after write:\n");
			std::string readcontent;
			readFile(filevector[i], readcontent);
			fprintf(stderr, "    file new content is '%s'\n", readcontent.c_str());
			appendFile(filevector[i], contentinfile);
			std::string readacontent;
			readFile(filevector[i], readacontent);
			fprintf(stderr, "read after append:\n");
			fprintf(stderr, "    file new content is '%s'\n", readacontent.c_str());
			
			fprintf(stderr, "now rename this file\n");
			renameFile(filevector[i], "createintest");
			if (existFile(filevector[i])) fprintf(stderr, "old file '%s' still exist\n", filevector[i].c_str());
			if (existFile("createintest")) fprintf(stderr, "rename file exist\n");
			fprintf(stderr, "now deleting new file\n");
			deleteFile("createintest");
			if (existFile("createintest")) fprintf(stderr, "delete failed\n");
			else fprintf(stderr, "delete successfully\n");
		}
	}
	
	return 0;
}
