//#pragma once
#ifndef MASTERINFO_H_
#define MASTERINFO_H_

#include <stdio.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <set>

class masterInfo{
	private:
		struct sockaddr_in master_addr;
		std::map<int, std::vector<int>> replicaInfo;
		//std::vector<std::map<>> ;
		std::vector<struct sockaddr_in> serverlist;
		std::vector<int> primarylist;
		std::vector<std::set<int>> grouplist;
		bool isprimary;
		void setPrimary();
	public:
		int socketfd;
		struct in_addr ip;
		int port;
		masterInfo();
		~masterInfo();
		/*readConfig will set master_addr, serverlist*/
		int readConfig(const char*);
		bool isPrimary(){
			return isprimary;
		}		
};
#endif /*SERVERINFO_H_*/
