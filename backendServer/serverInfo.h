//#pragma once
#ifndef SERVERINFO_H_
#define SERVERINFO_H_

#include <stdio.h>
#include <netinet/in.h>
#include <vector>


class serverInfo{
	private:
		struct sockaddr_in myaddr;
		int myID;
		struct sockaddr_in master_addr;
		struct sockaddr_in primary_addr;
		std::vector<struct sockaddr_in> replicas_addr;
		std::vector<struct sockaddr_in> serverlist;
		bool isprimary;
		
	public:
		int socketfd;
		struct in_addr ip;
		int port;
		serverInfo();
		~serverInfo();
		/*readConfig will set master_addr, serverlist, myaddr, myID*/
		int readConfig(const char*, int);
		void setPrimary(int);
		
		bool isPrimary(){
			return isprimary;
		}
		void addReplica(int replicaID){
			replicas_addr.push_back(serverlist[replicaID-1]);
		}
		std::vector<struct sockaddr_in> getReplicas(){
			return replicas_addr;
		}		
};
#endif /*SERVERINFO_H_*/
