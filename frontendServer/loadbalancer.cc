#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;


struct Server {
	string forward_addr;
	string bind_addr;
	bool running;

	Server(string forward_addr, string bind_addr) {
		this->forward_addr = forward_addr;
		this->bind_addr = bind_addr;
		running = false;
	}
};

vector<Server> servers;
map<sockaddr_in, int> connections;

int debug = 0;

sockaddr_in parse_addr(char* address) {

	char address_copy[100] = "";
	strcpy(address_copy, address);

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;

	// IP
	char* token = strtok(address_copy, ":");
	inet_pton(AF_INET, token, &addr.sin_addr);

    // port
	token = strtok(NULL, ":");
	addr.sin_port = htons(atoi(token));

	return addr;

}

void* check_server_status(void* arg) {
	for (int i = 0; i < servers.size(); i++) {

	}
}


int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "no argument provided.\n");
		exit(1);
	}

	int c;
	int port_number = 10000;

	// read in command line argument and process option
	while ((c = getopt(argc, argv, "vp:")) != -1) {
		switch (c) {
		case 'p':
			port_number = atoi(optarg);
			break;
		case 'v':
			debug = 1;
			break;
		case '?':
			if (isprint(optopt)) {
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			} else {
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			}
			return 1;
		default:
			break;
		}
	}

	if (optind >= argc) {
		fprintf(stderr, "file name is not provided. \n");
		exit(EXIT_FAILURE);
	}

	string filename = argv[optind];

	optind++;
	if (optind >= argc) {
		fprintf(stderr, "index of the current server instance is not provided. \n");
		exit(EXIT_FAILURE);
	}

	// read configuration file to get the bind address for a list of frontend servers
	char* forward_addr = NULL;
	char* bind_addr = NULL;

	char full_addr[1000] = "";


	string line;
	ifstream myfile(filename);
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			strcpy(full_addr, line.c_str());

			forward_addr = strtok(full_addr, ",");
			bind_addr = strtok(NULL, ",");

			if (debug == 1) {
				printf("forward address is %s \n", forward_addr);
			}

			Server server(forward_addr, bind_addr);

			servers.push_back(server);

		}
		myfile.close();
	} else {
		cout << "Unable to open configuration file";
	}

	// 1. socket: creates a socket descriptor
	int listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;

	// configure the server
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(port_number);

	// 2. bind: use the socket and associate it with the port number
	bind(listen_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));


	 // 3. listen to the port to which we bound; second arg is number of allowed connections
	listen(listen_fd, 10);

	// once you get here, the server is set up and about to start listening
	printf("\nServer configured to listen on port %d\n", port_number);
	fflush(stdout);

	while (true) {

		struct sockaddr_in clientaddr;
		socklen_t clientaddrlen = sizeof(clientaddr);

		// 4. accept: wait here until we get a connection on that port
		int comm_fd = accept(listen_fd, (struct sockaddr*) &clientaddr,
				&clientaddrlen);

		printf("Server got a connection from (%s, %d)\n", inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));

		if (comm_fd < 0) {
			close(comm_fd);
			exit(1);
		}

		if (debug == 1) {
			fprintf(stderr, "[%d] New connection \n", comm_fd);
			fprintf(stderr,
					"[%d] S: +OK Server ready (Author: Shiqing Liu / sliu118)\r\n",
					comm_fd);
		}

		write(comm_fd, "+OK Server ready (Author: Shiqing Liu / sliu118)\r\n",
				strlen("+OK Server ready (Author: Shiqing Liu / sliu118)\r\n"));

	}

	close(listen_fd);
	return 0;

}





