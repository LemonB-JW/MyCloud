#include <stdio.h> //FILE type
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "../../lib/masterInfo.h"

#ifndef panic
#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0) 
#endif

std::string addrTOstr(in_addr_t ip, int port)
{
  struct in_addr addr;
  addr.s_addr = ip;
  char buf[150];
  sprintf(buf, "%s:%d", inet_ntoa(addr), port);
  std::string saddr(buf);
  return saddr;
}

int masterInfo::readConfig(const char* filename){
	// read file and find my ip and port
	FILE *infile = fopen(filename, "r");
	if (!infile) 
		panic("Cannot read server list from '%s'\n", filename);
	int numServers = 0;
	char linebuf[100];
	
	//the first line in the config file is master's address
	if (fgets(linebuf, 100, infile)!= NULL){
		char *sproxyaddr = strtok(linebuf, ",\r\n");
	  char *srealaddr = sproxyaddr ? strtok(NULL, ",\r\n") : NULL;
	  master_saddr = sproxyaddr;
	  char *sip = strtok(sproxyaddr, ":");
	  char *sport = strtok(NULL, ":\r\n");	
	  bzero((void*)&master_addr, sizeof(master_addr));
	  master_addr.sin_family = AF_INET;
	  inet_aton(sip, &(master_addr.sin_addr));
	  port = atoi(sport);
	  master_addr.sin_port = htons(port);
	}
	
	while	(fgets(linebuf, 100, infile)!= NULL){
		char *sproxyaddr = strtok(linebuf, ",\r\n");
	  char *srealaddr = sproxyaddr ? strtok(NULL, ",\r\n") : NULL;  
	  char *sip = strtok(sproxyaddr, ":");
	  char *sport = strtok(NULL, ":\r\n");	  
  
	  //store all forwarding address in server list
	  struct sockaddr_in temp;
	  bzero((void*)&temp, sizeof(temp));
	  temp.sin_family = AF_INET;
	  inet_aton(sip, &temp.sin_addr);
	  temp.sin_port = htons(atoi(sport));
	  serverlist.push_back(temp);
	}
	fclose(infile);
	fprintf(stderr, "finish readConfig file\n");
	setPrimary();
	
}

void masterInfo::setPrimary(){
	int remainS = serverlist.size();
	int groupID = 0;
	int primaryIdx = 0;
	std::vector<int> replica;
	//at least 3 servers in a group
	fprintf(stderr, "inside setPrimary\n");
	while (remainS >= 6){
		primaryIdx = groupID*3;
		replicaInfo[primaryIdx] = replica;
		for (int i = 0; i < 3; i++){
			replicaInfo[primaryIdx].push_back(primaryIdx+i);
			myprimary[primaryIdx+i] = primaryIdx;
		}
		groupID++;
		remainS -= 3;
	}
	
	if (remainS > 0){
		primaryIdx = groupID*3;
		replicaInfo[primaryIdx] = replica;
		for (int i = 0; i < remainS; i++){
			replicaInfo[primaryIdx].push_back(primaryIdx+i);
			myprimary[primaryIdx+i] = primaryIdx;
		}
		groupNum = groupID + 1;
		remainS = 0;		
	}
	fprintf(stderr, "leaving setPrimary\n");
}

bool masterInfo::isPrimary(int index){
	if (replicaInfo.find(index) == replicaInfo.end())
		return false;
	return true;
}

int masterInfo::getPrime(int index){
	if (myprimary.find(index) == myprimary.end())
		return -1;
	return myprimary[index];
}


std::vector<int> masterInfo::getSub(int primeIdx){
	std::vector<int> sublist;
	if (replicaInfo.find(primeIdx) == replicaInfo.end())
		return sublist;
	for (int i = 0; i < replicaInfo[primeIdx].size(); i++){
		if (replicaInfo[primeIdx][i] != primeIdx){
			sublist.push_back(replicaInfo[primeIdx][i]);
		}
	}
	return sublist;
}

bool masterInfo::isAlive(int serverIdx){
	if (deadlist.find(serverIdx) == deadlist.end())
		return false;
	return true;
}

int masterInfo::promoteNewPrimary(int oldPrimaryIdx){
	std::vector<int> replicas = replicaInfo[oldPrimaryIdx];
	for(int i = 0; i < replicas.size(); i++){
		if (replicas[i] != oldPrimaryIdx && isAlive(replicas[i])){
			/*need to add mutax here when make changes to replicaInfo list*/
			replicaInfo[replicas[i]] = replicas;
			replicaInfo.erase(oldPrimaryIdx);
		}
	}
}

std::string masterInfo::getServers(int groupId){
	std::vector<int> replicas;
	std::map<int, std::vector<int>>::iterator itr = replicaInfo.begin();
	for (int i = 0; i<groupId; i++){
		itr++;
	}
	//itr = itr+ groupId;
	replicas = itr->second;
	std::string servers;
	for (int i = 0; i < replicas.size(); i++){
		if (i != 0)
			servers.append(",");
		servers.append(addrTOstr(serverlist[replicas[i]].sin_addr.s_addr, ntohs(serverlist[replicas[i]].sin_port)));
	}
	servers.append("\r\n");
	return servers;
}

