#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <set>
#include <iterator>
#include <dirent.h>
#include <sys/file.h>
#include "MailServiceGRPC.h"

int pflag = 0;
int aflag = 0;
int vflag = 0;
std::set<std::string> mailboxes;


pthread_t tid[1000];
pthread_mutex_t locks[1500];

int thread_count = 0;

static bool running = true;

std::vector<int*> sockets;
std::string master_addr;




// void signal_handler(int signum) {
//     running = false;

//     close(*comm_fd_list[0]);

//     for (int i = 1; i < comm_fd_list.size(); i++) {
//     	write(*comm_fd_list[i], "421 Closing connection\r\n", strlen("421 Closing connection\r\n"));
//     	if (vflag == 1) {
//     		fprintf(stderr, "[%d] Connection closed\r\n", *comm_fd_list[i]);
//     	}
//     	close(*comm_fd_list[i]);
//     	pthread_detach(tid[i - 1]);
//     }
//     exit(signum);

// }



void send_response(int fd, const char* response) {
	if (vflag == 1) {
		fprintf(stderr, "[%d] S: %s", fd, response);
	}

	write(fd, response, strlen(response));

}



void write_data(int fd, char* buffer, std::set<std::string>& recipients, char* sender, bool& inmessage, char* text) {

	if (strstr(buffer, "\r\n") != NULL) {
		// continue to read email text
		if (strcmp(buffer, ".\r\n") != 0) {
			strcat(text, buffer);
			memset(buffer, 0, 2000);

		}
		// reach end of email text
		else {
			time_t mytime = time(NULL);
			char *time_str = ctime(&mytime);
			time_str[strlen(time_str) - 1] = '\0';

			//add header to email text
			char email[5000] = "";
			strcat(email, "From <");
			strcat(email, sender);
			strcat(email, "> ");
			strcat(email, time_str);
			strcat(email, "\r\n");
			strcat(email, text);


// 			for (set<string>::iterator it = recipients.begin(); it != recipients.end(); it++) {
// 				// critical section - BEGIN
// 				int pos = distance(mailboxes.begin(), mailboxes.find(*it));
// 				pthread_mutex_lock(&locks[pos]);
// 				FILE * fp;
// 				strcat(directory, "/");
// 				strcat(directory, (*it).c_str());
// 				fp = fopen (directory,"a");
// 				int fd = fileno(fp);
// 				int ret = flock(fd, LOCK_EX | LOCK_NB);
// //				if (ret = -1) {
// //					exit(0);
// //				}

// 				fputs(email, fp);
// 				flock(fd, LOCK_UN);
// 				fclose(fp);

// //				ofstream mailbox;
// //				mailbox.open(string(directory) + "/" + (*it), ios_base::app);
// //
// //				mailbox << email;
// //				mailbox.close();

// 				// critical section - END
// 				pthread_mutex_unlock(&locks[pos]);
// 			}


			inmessage = false;
			memset(buffer, 0, 2000);
			memset(sender, 0, 100);
			memset(text, 0, 5000);
			recipients.clear();

			send_response(fd, "250 OK\r\n");
		}
	}

}



void* handle_local_request(void *thread_data) {

	int fd = *(int*) thread_data;
	char character[5] = "";
	char buffer[2000] = "";
	char command[5] = "";
	bool inmessage = false;
	char sender[100] = "";
	char text[5000] = "";
	std::set<std::string> recipients;

	int state = 0;

	// 0 READY
	// 1 CONNECTED
	// 2 MAIL
	// 3 RCPT
	// 4 DATA
	// 5 QUIT
	// 6 RSET


	send_response(fd, "220 localhost service ready\r\n");

	while (true) {


		memset(character, 0, 5);

		int read_size = read(fd, character, 1);

		strcat(buffer, character);

		if (!inmessage) {

			if (strstr(buffer, "\r\n") != NULL) {

				if (vflag == 1) {
					fprintf(stderr, "[%d] C: %s", fd, buffer);
				}

				if (strlen(buffer) < 6) {
					send_response(fd, "501 Syntax error in parameters or arguments\r\n");
					//clear the buffer
					memset(buffer, 0, 2000);
					continue;
				} else {
					//parse command
					for (int i = 0; i < 4; i++) {
						command[i] = buffer[i];
					}
					command[4] = '\0';
				}

				// handle different command cases
				if (strcasecmp(command, "HELO") == 0) {
					if (state > 1) {
						send_response(fd, "503 Bad sequence of commands\r\n");
					} else {
						send_response(fd, "250 localhost\r\n");
						state = 1;
					}

				} else if (strcasecmp(command, "MAIL") == 0) {
					if (strlen(buffer) <= 12) {
						send_response(fd, "501 Syntax error in parameters or arguments\r\n");
						//clear the buffer
						memset(buffer, 0, 2000);
						continue;
					}

					char extra[6] = "";
					for (int i = 5, k = 0; i < 10; i++, k++) {
						extra[k] = buffer[i];
					}
					extra[5] = '\0';

					if (strcasecmp(extra, "FROM:") != 0) {
						send_response(fd, "500 Syntax error, command unrecognized\r\n");
						memset(buffer, 0, 2000);
						continue;
					}

					if (state != 1) {
						send_response(fd, "503 Bad sequence of commands\r\n");
						memset(buffer, 0, 2000);
						continue;
					}

					char copy[100] = "";
					for (int a = 11, b = 0; a < strlen(buffer) - 3; a++, b++) {
						copy[b] = buffer[a];
					}

					copy[strlen(copy)] = '\0';
					char* address = NULL;
					char* domain = NULL;




					address = strtok(copy, "@");
					domain = strtok(NULL, "@");



					if (domain == NULL
							|| strcasecmp(domain, "localhost") != 0) {
						send_response(fd,
								"501 Syntax error in parameters or arguments\r\n");
					} else {
						state = 2;
						strcpy(sender, copy);
						send_response(fd, "250 OK\r\n");
					}

				} else if (strcasecmp(command, "RCPT") == 0) {
					if (strlen(buffer) <= 9) {
						send_response(fd,
								"501 Syntax error in parameters or arguments\r\n");
						//clear the buffer
						memset(buffer, 0, 2000);
						memset(character, 0, 5);
						continue;
					}

					char extra[5] = "";
					for (int i = 4, k = 0; i < 8; i++, k++) {
						extra[k] = buffer[i];
					}
					extra[4] = '\0';

					if (strcasecmp(extra, " TO:") != 0) {
						send_response(fd,
								"500 Syntax error, command unrecognized\r\n");
						memset(buffer, 0, 2000);
						continue;
					}

					if (state < 2 || state > 3) {
						send_response(fd, "503 Bad sequence of commands\r\n");
						memset(buffer, 0, 2000);
						continue;
					}

					char copy[100] = "";
					for (int a = 9, b = 0; a < strlen(buffer) - 3; a++, b++) {
						copy[b] = buffer[a];
					}

					copy[strlen(copy)] = '\0';

					char *address = NULL;
					char *domain = NULL;

					printf("full email is %s\n", copy);

					address = strtok(copy, "@");
					domain = strtok(NULL, "@");

					printf("address is %s\n", address);
					printf("domain %s \n", domain);

					if (domain == NULL
							|| strcasecmp(domain, "localhost") != 0) {
						send_response(fd,
								"501 Syntax error in parameters or arguments\r\n");
					} else {
						// check if the user exists in the mailbox directory
						strcat(address, ".mbox");
						if (mailboxes.find(address) != mailboxes.end()) {
							state = 3;
							recipients.insert(address);
							send_response(fd, "250 OK\r\n");
						}
						else {
							send_response(fd, "550 Mailbox unavailable\r\n");
						}
					}

				} else if (strcasecmp(command, "DATA") == 0) {

					if (state < 3 || state > 4) {
						send_response(fd, "503 Bad sequence of commands\r\n");
					}
					else {
						inmessage = true;
						state = 4;
						send_response(fd, "354 send the mail data, end with .\r\n");
					}

				} else if (strcasecmp(command, "QUIT") == 0) {
					state = 5;
					send_response(fd, "221 localhost Service closing transmission channel\r\n");
					break;

				} else if (strcasecmp(command, "RSET") == 0) {
					// aborts
					if (state == 0) {
						send_response(fd, "503 Bad sequence of commands\r\n");
					}
					else {
						state = 1;
						memset(buffer, 0, 2000);
						memset(sender, 0, 100);
						recipients.clear();
						send_response(fd, "250 OK\r\n");
					}

				} else if (strcasecmp(command, "NOOP") == 0) {

					send_response(fd, "250 OK\r\n");

				} else {
					send_response(fd, "500 Unknown command\r\n");
				}
				//clear the buffer
				memset(buffer, 0, 2000);
			}

		}
		else {
			write_data(fd, buffer, recipients, sender, inmessage, text);
		}

	}


	close(fd);
	memset(buffer, 0, 2000);
	if (vflag == 1) {
		fprintf(stderr, "[%d] Connection closed\r\n", fd);
	}

	pthread_exit(NULL);
}


void* runGRPCServer(void* thread_arg) {

	int port_number = *(int*)thread_arg;

	std::string server_address = "127.0.0.1:" + std::to_string(port_number);

	MailServiceGRPC service;

	ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
  // Finally assemble the server.
	std::unique_ptr<Server> server(builder.BuildAndStart());
	std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
	server->Wait();
}


// main thread for GRPC and as soon as remote email arrives, create a new thread 
int main(int argc, char *argv[]) {

	int c;
	unsigned int port_number = 2500;

	// read in command line argument and process option
	while ((c = getopt(argc, argv, "vp:")) != -1) {
		switch (c) {
		case 'p':
			pflag = 1;
			port_number = atoi(optarg);
			break;
		case 'v':
			vflag = 1;
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


	// if (optind == argc) {
	// 	fprintf(stderr, "Missing master node address.\n");
	// 	exit(1);
	// }

	// master_addr = std::string(argv[optind]);

	int port_number_grpc = 4000;

	pthread_create(&tid[thread_count], NULL, &runGRPCServer, &port_number_grpc);

	thread_count++;



	master_addr = "127.0.0.1:8001";


	// create a new socket
	int listen_fd = socket(PF_INET, SOCK_STREAM, 0);

	if (listen_fd < 0) {
		printf("cannot open socket\r\n");
		exit(2);
	}

	// save server socket
	sockets.push_back(&listen_fd);
	

	// reuse port
	const int REUSE = 1;
	setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &REUSE, sizeof(REUSE));

	char bind_addr[100] = "127.0.0.1";

	// bind port
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;

	// set IP
	// servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	inet_pton(AF_INET, bind_addr, &servaddr.sin_addr);

	// set port 
	servaddr.sin_port = htons(port_number);
	bind(listen_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	listen(listen_fd, 10);

	// once you get here, the server is set up and about to start listening
	printf("Server configured to listen on (%s, %d)\n", inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
	fflush(stdout);

	while (true) {

		struct sockaddr_in client_addr;
		socklen_t clientaddrlen = sizeof(client_addr);

		int comm_fd = accept(listen_fd, (struct sockaddr*) &client_addr,
				&clientaddrlen);


		sockets.push_back(&comm_fd);

		if (vflag == 1) {
			printf("Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
			fprintf(stderr, "[%d] New connection \n", comm_fd);
			fprintf(stderr, "[%d] S: +OK Server ready (Author: Shiqing Liu / sliu118)\r\n", comm_fd);
		}

		pthread_create(&tid[thread_count], NULL, &handle_local_request, &comm_fd);

		thread_count++;
	}


	close(listen_fd);

	return 0;
}



