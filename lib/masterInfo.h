//#pragma once
#ifndef MASTERINFO_H_
#define MASTERINFO_H_

#include <stdio.h>
//#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <map>
#include <string>
#include <unordered_set>

class masterInfo{
	private:
		std::string mf_addr;//master frontend grpc addr
		std::string mb_addr;//master backend grpc addr
		std::map<int, std::vector<int>> replicaInfo;//find replica based on primary index, also served as a primary set( keys are primaries), also can found primary based on group number( iterator + groupID -> first)
		std::vector<int> myprimary; //find primary based on server index
		std::vector<int> checkpointV; //checkpoint version do i need this or primary server need this?
		std::unordered_set<int> deadlist;
		std::vector<std::string> bf_addr_list;//backend frontend grpc address
		std::vector<std::string> bm_addr_list;//backend master grpc address
		int groupNum;
		void setPrimary();//decide group and primary, called in readConfig
		
	public:
		int getGroupNum(){
			return groupNum;
		}
		
		const std::string& getMFaddr() const{
			return mf_addr;
		}
		
		const std::string& getMBaddr() const{
			return mb_addr;
		}
		
		const std::string& getBMaddr(int index) const{
			return bm_addr_list[index];
		}
		
		masterInfo(){}
		~masterInfo(){}
		/*readConfig will set master_addr, serverlist and assign group and primary*/
		int readConfig(const char*);
		bool isPrimary(int); //given a kvstore server index, return true if it is a primary node
		int getPrime(int); //get prime index given sub index, if prime index given, return itself
		std::vector<int> getSub(int); //return a list of sub index given prime index
		bool isAlive(int);	
		int promoteNewPrimary(int); //promote a new primary given old primary
		std::vector<std::string> getServers(int);
};
#endif /*MASTERINFO_H_*/
