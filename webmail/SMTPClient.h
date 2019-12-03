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

	string lookUpIP(string& domain);

	void sendCommand(string& domain, string& message, string& sender, string& recipient);

	bool deliverMail();

	void parseRecord(char* buffer, int& priority, char* address);

	void sendResponse(int fd, string response);
}