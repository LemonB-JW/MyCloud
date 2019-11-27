/*
	Author: Peng Li
	
*/

//#pragma once
#ifndef SERVERINFO_H_
#define SERVERINFO_H_

#include <stdio.h>
#include <vector>
#include <string>


class serverInfo{
	private:
		std::string master_addr; //master server address used to communicate with backend servers
		std::string primary_addr;
		std::string myaddr_front; //my GRPC address used to communicate with frontend servers
		int myIdx;
		
		std::vector<int> replicas_idx; //all replica index in my group (including myself)
		std::vector<string> serverlist; //all server GRPC address used to communicate with other backend servers
		bool isprimary; //true if I am primary, otherwise false
		
		int status; //0: initlizing, 1: normal, 2: recovering
		//file paths using
		std::string FILE_PATH;//server folder path
		std::string LOG_PATH;//log pth of current server
		std::string CHECKPOINT_PATH;//checkpoint path of current server
		
		long mySeq;//current command sequence
		bool checkpointState;//true if it can perform a check point, otherwise cannot checkpoint: cannot checkpoint during writing or checkpointing, can checkpoint when read only or idle 
		
		pthread_mutex_t mySeqMutex;//lock for my seq		
		pthread_mutex_t mapMutex;//lock for the whole map
		
	public:	
		serverInfo();
		~serverInfo();
		/*readConfig will set master_addr, serverlist, myaddr, myID*/
		void readConfig(const char*, int);
		
		const std::string& getMasterAddr() const{
			return master_addr;
		}
		const std::string& getPrimaryAddr() const{
			return primary_addr;
		}
		
		bool setPrimary(int); //set primary_addr with primary index, return true if set successfully, return false if index is out of bound
		
		
		const std::string& getMyAddrFront() const{
			return myaddr_front;
		}
		
		const std::string& getMyAddrBack() const{
			return serverlist[myIdx];
		}
		
		const int getMyIndex(){
			return myIdx;
		}
		
		const std::string& getServerAddr(int serverIndex) const{
			return serverlist[serverIndex];
		}
		
		const std::vector<int>& getReplicas() const{
			return replicas_idx;//return vector<string> or vector<int>???
		}
		
		void addReplica(int replicaIndex){
			replicas_idx.push_back(replicaIndex);
		}
		
		bool isPrimary(){
			return isprimary;
		}
			
		//void printServerInfo();	
		
		int getStatus() const{
			return status;
		}
		
		void setStatus(int s){
			status = s;
		}
		
		std::string getFilePath() const {
			return FILE_PATH;
		}
		
		std::string getLogPath() const {
			return LOG_PATH;
		}
		
		std::string getCheckpointPath() const {
			return CHECKPOINT_PATH;
		}
		
		bool checkpointStatus() {
			return checkpointState;
		}
		
		void pauseCheckpoint() {
			checkpointState = false;
		}
		
		void resumeCheckpoint() {
			checkpointState = true;
		}
		
		void setFilePath(const std::string& filePath) {
			FILE_PATH = filePath;
			LOG_PATH = FILE_PATH + "/log.txt";
			CHECKPOINT_PATH = FILE_PATH + "/checkpoint.txt";
		}
				
		void updateMySeq(long);	
		long increseMySeq();
		void lockMap();
		void unlockMap();		
};
#endif /*SERVERINFO_H_*/



