#ifndef SMTPCLIENT_H
#define SMTPCLIENT_H

#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <string>

#define N 4096

class SMTPClient {

public: 

	std::string lookUpIP(std::string domain);

	void sendCommand(std::string domain, std::string message, std::string sender, std::string recipient);

	// bool deliverMail();

	void parseRecord(char* buffer, int& priority, char* address);

	// void sendResponse(int fd, std::string response);
};

#endif