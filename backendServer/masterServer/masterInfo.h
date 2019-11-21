//#pragma once
#ifndef MASTERINFO_H_
#define MASTERINFO_H_

#include <stdio.h>
//#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class masterInfo{
	private:
		
		std::unordered_map<int, std::vector<int>> replicaInfo;//find replica based on primary index, also server as a primary set( keys are primaries )
		std::unordered_map<int, int> myprimary; //find primary based on server index
		std::vector<struct sockaddr_in> serverlist;
		std::unordered_set<int> deadlist;
		void setPrimary();//decide group and primary, called in readConfig
		
	public:
		struct sockaddr_in master_addr;
		int port;
		masterInfo();
		~masterInfo();
		/*readConfig will set master_addr, serverlist and assign group and primary*/
		int readConfig(const char*);

		bool isPrimary(int);	
		int getPrime(int);
		std::vector<int> getSub(int);
		bool isAlive(int);	
		int promoteNewPrimary(int);
		//std::string getSub();
};
#endif /*MASTERINFO_H_*/
