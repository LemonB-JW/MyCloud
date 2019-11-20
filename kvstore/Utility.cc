#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <time.h>
#include <sys/time.h>
#include "Utility.h"
using namespace std;

string generateFileID(int worker_index, int sequence_num) {
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
	return to_string(worker_index) + to_string(sequence_num) + timestamp;
} 






