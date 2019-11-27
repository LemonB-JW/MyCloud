/*
	Author: Peng Li
	
*/

#include <stdio.h> //FILE type
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string.h>

#include "serverInfo.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

serverInfo::serverInfo(){
	isprimary = false;	
	status = 0; //0: initlizing, 1: normal, 2: recovering
	FILE_PATH = ".";
	LOG_PATH = "/log.txt";//binary or txt, need to decide
	CHECKPOINT_PATH = "/checkpoint.txt;
	mySeq = 0;
	checkpointState = true;
	
	if (pthread_mutex_init(&mySeqMutex, NULL)) ;//init lock for mySeq
	pthread_mutex_init(&mapMutex, NULL);//init lock for map???
}

serverInfo::~serverInfo(){
	pthread_mutex_destroy(&mySeqMutex);
	pthread_mutex_destroy(&mapMutex);//must make sure mapMutex is unlock!
}

void serverInfo::readConfig(const char* filename, int pos){
	// read file and find my ip and port
	FILE *infile = fopen(filename, "r");
	if (!infile) 
		panic("Cannot read server list from '%s'\n", filename);
	int numServers = 0;
	char linebuf[100];
	
	//the first line in the config file is master's address
	if (fgets(linebuf, 100, infile)!= NULL){
		char *sfrontaddr = strtok(linebuf, ",\r\n");
	  char *sbackaddr = sfrontaddr ? strtok(NULL, ",\r\n") : NULL;
	  if (sbackaddr == NULL) master_addr = sfrontaddr;
	  else master_addr = sbackaddr;
	}
	
	while	(fgets(linebuf, 100, infile)!= NULL){
		char *sfrontaddr = strtok(linebuf, ",\r\n");
	  char *sbackaddr = sfrontaddr ? strtok(NULL, ",\r\n") : NULL;
	  std::string temp;
	  if (sbackaddr == NULL) temp = sfrontaddr;
	  else temp = sbackaddr;
	  serverlist.push_back(temp);
	  numServers++;
		if (numServers == pos){
			myIdx = pos - 1;//index 
			myaddr_front = sfrontaddr;
		}	
	}
	//finish reading config file
}


bool serverInfo::setPrimary(int primaryIdx){
	if (primaryIdx >= serverlist.size()) return false;
	primary_addr = serverlist[primaryIdx];
	if (primaryIdx == myIdx)
		isprimary = true;
	else isprimary = false;
	return true;
}


void serverInfo::updateMySeq(long seq){
	pthread_mutex_lock(&mySeqMutex);
	mySeq = std::max(mySeq, seq);
	pthread_mutex_unlock(&mySeqMutex);
}


long serverInfo::increaseMySeq(){
	//long newSeq;
	pthread_mutex_lock(&mySeqMutex);
	mySeq++;
	//newSeq = mySeq;
	pthread_mutex_unlock(&mySeqMutex);
	return mySeq;//newSeq
}

void serverInfo::lockMap(){
	pthread_mutex_lock(&mapMutex);
}

void serverInfo::unlockMap(){
	pthread_mutex_unlock(&mapMutex);
}



