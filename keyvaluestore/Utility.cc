// Author: Jiaying Guo

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include "../lib/Utility.h"
using namespace std;

string Utility::generateFileID(string path_name) {
	struct timeval tv;
	time_t nowtime;
	struct tm *nowtm;
	char tmbuf[200], final_formatted_tm[200];
	memset(tmbuf, 0, 200);
	memset(final_formatted_tm, 0, 200);
	gettimeofday(&tv, NULL);
	nowtime = tv.tv_sec;
	nowtm = localtime(&nowtime);
	strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
	snprintf(final_formatted_tm, sizeof(final_formatted_tm), "%s.%06ld", tmbuf, tv.tv_usec);
	string timestamp(tmbuf);
	string res = path_name + timestamp;
	return res;
} 

string Utility::parseFileName(string path_name){
	// root/lib/foo.txt
	int i = path_name.length() - 1;
	for(; i >= 0; i--){
		if(path_name.at(i) == '/') break;
	}
	return path_name.substr(i + 1);
}






