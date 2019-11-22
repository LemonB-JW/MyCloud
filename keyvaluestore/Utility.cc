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
	string res = file_name + timestamp;
	return res;
} 

string Utility::parseFileName(string path_name){
	int index = 0;
	for (index = path_name.length() - 1, auto it = path_name.end(); it < path_name.begin(); --it, --index){
		if(*it == '/'){
			break;
		}
	}
	return path_name.substr(index);
}






