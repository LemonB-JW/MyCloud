#include <stdlib.h>
#include <stdio.h>
#include <openssl/md5.h>
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


using namespace std;

int pflag = 0;
int aflag = 0;
int vflag = 0;
char directory[100];
set<string> mailboxes;
pthread_mutex_t locks[1000];


pthread_t tid[1000];
int count = 0;

static bool running = true;

vector<int*> comm_fd_list;

struct Message {
	string text;
	bool deleted;
	Message(string text) {
		this->text = text;
		deleted = false;
	}
};

void signal_handler(int signum) {
    running = false;
    for (int i = 0; i < comm_fd_list.size(); i++) {
    	write(*comm_fd_list[i], "-ERR Server shutting down\r\n", strlen("-ERR Server shutting down\r\n"));
    	if (vflag == 1) {
    		fprintf(stderr, "[%d] Connection closed\r\n", *comm_fd_list[i]);
    	}
    	close(*comm_fd_list[i]);
    	pthread_detach(tid[i]);
    }
    exit(signum);

}


void computeDigest(char *data, int dataLengthBytes, unsigned char *digestBuffer)
{
  /* The digest will be written to digestBuffer, which must be at least MD5_DIGEST_LENGTH bytes long */

  MD5_CTX c;
  MD5_Init(&c);
  MD5_Update(&c, data, dataLengthBytes);
  MD5_Final(digestBuffer, &c);
}

void send_response(int fd, const char* response) {
	if (vflag == 1) {
		fprintf(stderr, "[%d] S: %s", fd, response);
	}

	write(fd, response, strlen(response));

}



void write_data(int fd, char* buffer, set<string>& recipients, char* sender, bool& inmessage) {

	char text[5000] = "";

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
			char email[5000];
			email[0] = '\0';
			strcat(email, "From <");
			strcat(email, sender);
			strcat(email, ">");
			strcat(email, time_str);
			strcat(email, text);

			for (set<string>::iterator it = recipients.begin(); it != recipients.end(); it++) {
				ofstream mailbox;
				mailbox.open(string(directory) + "/" + (*it), ios_base::app);
				mailbox << email;
				mailbox.close();
			}

			inmessage = false;
			memset(buffer, 0, 2000);
			memset(sender, 0, 100);
			recipients.clear();

			send_response(fd, "250 OK\r\n");
		}
	}

}

void read_messages(vector<Message>& messages, vector<string>& headers, char* user) {


	ifstream mailbox;
	mailbox.open(string(directory) + "/" + string(user), ios_base::in);

	string line = "";
	string text = "";
	int count = 0;

	while(getline(mailbox, line)) {

		if (line.find("From ") != string::npos) {

			// add the current header
			line.pop_back();
			line += "\r\n";
			headers.push_back(line);

			// add the last message
			messages.push_back(Message(text));
			text = "";

		}
		else {

			// append email text
			line.pop_back();
			line += "\r\n";
			text += line;
		}

	}

	// add the last message
	if (!messages.empty()) {
			messages.erase(messages.begin());
			messages.push_back(Message(text));
	}

	mailbox.close();

}

void generate_uidl(int fd, vector<Message>& messages, int index, bool ok) {
	if (index < 1 || index > messages.size() || messages[index - 1].deleted) {
		send_response(fd, "-ERR no such message");
	}
	else {
		unsigned char digest[MD5_DIGEST_LENGTH];
		char uid[MD5_DIGEST_LENGTH + 1];
		char data[messages[index - 1].text.length() + 1];
		strcpy(data, messages[index - 1].text.c_str());
		computeDigest(data, strlen(data), digest);

		for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
			sprintf(uid + i, "%02x", digest[i]);
		}

		string res = "";

		if (ok) {
			res = "+OK " + to_string(index) + " " + string(uid) + "\r\n";
		}
		else {
			res = to_string(index) + " " + string(uid) + "\r\n";
		}

		send_response(fd, res.c_str());


	}

}

void list_messages(int fd, vector<Message>& messages, int index, bool ok) {

	if (index < 1 || index > messages.size() || messages[index - 1].deleted) {
		send_response(fd, "-ERR no such message");
	}
	else {

		int len = messages[index - 1].text.length();

		string res;

		if (ok) {
			res = "+OK " + to_string(index) + " " + to_string(len) + "\r\n";
		}
		else {
			res = to_string(index) + " " + to_string(len) + "\r\n";
		}

		send_response(fd, res.c_str());
	}

}

void parse_arg(char* buffer, char* arg) {

	char copy[1000] = "";
	strcpy(copy, buffer);
	arg[0] = copy[4];
	arg[1] = copy[5];
	arg[2] = '\0';


	// no argument
	if (strcmp(arg, "\r\n") == 0) {
		arg[0] = '\0';
	}
	else {
		memset(arg, 0, 100);
		for (int i = 5, k = 0; i < strlen(copy) - 2; i++, k++) {
			arg[k] = copy[i];
		}
		arg[strlen(arg)] = '\0';
	}

}

void update_mailbox(vector<Message>& messages, vector<string>& headers, char* user) {
	ofstream mailbox;
	mailbox.open(string(directory) + "/" + string(user), ios_base::out | ios_base::trunc);

	for (int i = 0; i < messages.size(); i++) {
		if (messages[i].deleted) {
			continue;
		}
		mailbox << headers[i];
		mailbox << messages[i].text;
	}
	mailbox.close();
}




void* handle_request(void *thread_data) {

	int fd = *(int*) thread_data;
	char character[5] = "";
	char buffer[2000] = "";
	char command[5] = "";
	bool inmessage = false;
	char sender[100] = "";
	set<string> recipients;

	char user[1000] = "";

	int state = 0;

	// 0 AUTHORIZATION
	// 1 TRANSACTION
	// 2 UPDATE


	vector<Message> messages;
	vector<string> headers;


	send_response(fd, "+OK POP3 ready [localhost]\r\n");

	while (true) {


		memset(character, 0, 5);

		int read_size = read(fd, character, 1);

		strcat(buffer, character);


			if (strstr(buffer, "\r\n") != NULL) {

				if (vflag == 1) {
					fprintf(stderr, "[%d] C: %s", fd, buffer);
				}

				if (strlen(buffer) < 6) {
					send_response(fd, "-ERR unkonwn command\r\n");
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
				if (strcasecmp(command, "USER") == 0) {
					if (state != 0) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					} else {
						char email[1000] = "";
						for (int i = 5, k = 0; i < strlen(buffer) - 2; i++, k++) {
							email[k] = buffer[i];
						}
						email[strlen(email)] = '\0';

						char *address = NULL;
						char *domain = NULL;

						address = strtok(email, "@");
						domain = strtok(NULL, "@");

						strcat(address, ".mbox");

						if (mailboxes.find(address) != mailboxes.end()) {
							strcpy(user, address);
							send_response(fd, "+OK Mailbox exists\r\n");
						}
						else {
							send_response(fd, "-ERR Mailbox unavailable\r\n");
						}

					}

				} else if (strcasecmp(command, "PASS") == 0) {
					if (state != 0 || strlen(user) == 0) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					}
					else {
						//parse password
						char password[100] = "";
						for (int i = 5, k = 0; i < strlen(buffer) - 2; i++, k++) {
							password[k] = buffer[i];
						}
						password[strlen(password)] = '\0';

						//validate password
						if (strcmp(password, "cis505") != 0) {
							memset(user, 0, 1000);
							send_response(fd, "-ERR Wrong password\r\n");
						}
						else {
							state = 1;
							send_response(fd, "+OK Maildrop locked and ready\r\n");
							// critical section-BEGIN
							int pos = distance(mailboxes.begin(), mailboxes.find(user));
							pthread_mutex_lock(&locks[pos]);
							read_messages(messages, headers, user);
						}

					}

				} else if (strcasecmp(command, "STAT") == 0) {
					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					}
					else {
						int count = 0;
						int size = 0;

						for (int i = 0; i < messages.size(); i++) {
							if (!messages[i].deleted) {
								count++;
								size += messages[i].text.length();
							}
						}

						string res = "+OK " + to_string(count) + " " + to_string(size) + "\r\n";
						send_response(fd, res.c_str());

					}

				} else if (strcasecmp(command, "UIDL") == 0) {
					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					}
					else {
						char arg[1000] = "";
						parse_arg(buffer, arg);

						if (strlen(arg) == 0) {
							string res = "+OK " + to_string(messages.size()) + " messages\r\n";
							send_response(fd, res.c_str());
							for (int i = 0; i < messages.size(); i++) {
								generate_uidl(fd, messages, i + 1, false);
							}
							send_response(fd, ".\r\n");
						}
						else {
							generate_uidl(fd, messages, atoi(arg), true);
						}

					}


				} else if (strcasecmp(command, "DELE") == 0) {
					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					}
					else {
						char arg[1000] = "";
						parse_arg(buffer, arg);
						if (strlen(arg) == 0) {
							send_response(fd, "-ERR Syntax error in parameters or arguments\r\n");
						}
						else {
							int index = atoi(arg);
							if (index < 1 || index > messages.size() || messages[index - 1].deleted) {
								send_response(fd, "-ERR no such message");
							}
							else {
								// if message has already been deleted
								if (messages[index - 1].deleted) {
									string res = "-ERR message " + to_string(index) + " already deleted\r\n";
									send_response(fd, res.c_str());
								}
								// if message has not been deleted
								else {
									messages[index - 1].deleted = true;
									string res = "+OK message " + to_string(index) + " deleted\r\n";
									send_response(fd, res.c_str());
								}

							}
						}

					}

				}
				else if (strcasecmp(command, "RETR") == 0) {
					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					} else {
						char arg[1000] = "";
						parse_arg(buffer, arg);

						if (strlen(arg) == 0) {
							send_response(fd,
									"-ERR Syntax error in parameters or arguments\r\n");
						} else {
							int index = atoi(arg);
							if (index < 1 || index > messages.size()
									|| messages[index - 1].deleted) {
								send_response(fd, "-ERR no such message");
							} else {

								string data = messages[index - 1].text;
								string header = "+OK "
										+ to_string(data.length())
										+ " octets\r\n";
								send_response(fd, header.c_str());


								// write mail line by line
								int end = 0;
								int start = 0;
								string line;

								while (start < data.length()) {
									end = data.find("\n", start);
									line = data.substr(start, end - start + 1);
									send_response(fd, line.c_str());
									start = end + 1;
								}

								send_response(fd, ".\r\n");

							}
						}

					}

				}
				else if (strcasecmp(command, "LIST") == 0) {

					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					} else {
						char arg[1000] = "";
						parse_arg(buffer, arg);

						if (strlen(arg) == 0) {
							string res = "+OK " + to_string(messages.size())
									+ " messages\r\n";
							send_response(fd, res.c_str());
							for (int i = 0; i < messages.size(); i++) {
								list_messages(fd, messages, i + 1, false);
							}
							send_response(fd, ".\r\n");
						} else {
							generate_uidl(fd, messages, atoi(arg), true);
						}

					}

				}
				else if (strcasecmp(command, "RSET") == 0) {
					if (state != 1) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					} else {

						for (int i = 0; i < messages.size(); i++) {
							if (messages[i].deleted) {
								messages[i].deleted = false;
							}
						}

						string res = "+OK maildrop has " + to_string(messages.size()) + "  messages\r\n";
						send_response(fd, res.c_str());
					}

				}
				else if (strcasecmp(command, "QUIT") == 0) {
					if (state == 0) {
						send_response(fd, "+OK localhost service closing transmission channel\r\n");
					}
					else if (state == 2) {
						send_response(fd, "-ERR Bad sequence of commands\r\n");
					}
					else {
						state = 2;
						send_response(fd, "+OK localhost service closing transmission channel\r\n");
						update_mailbox(messages, headers, user);
						// critical section-END
						int pos = distance(mailboxes.begin(), mailboxes.find(user));
						pthread_mutex_unlock(&locks[pos]);

					}
					break;

				}
				else if (strcasecmp(command, "NOOP") == 0) {
					send_response(fd, "+OK\r\n");
				} else {
					send_response(fd, "-ERR Not supported\r\n");
				}
				//clear the buffer
				memset(buffer, 0, 2000);
			}

	}


	close(fd);
	memset(buffer, 0, 2000);
	if (vflag == 1) {
		fprintf(stderr, "[%d] Connection closed\r\n", fd);
	}

	pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

	int c;
	unsigned int port_number = 11000;

	// read in command line argument and process option
	while ((c = getopt(argc, argv, "vap:")) != -1) {
		switch (c) {
		case 'p':
			pflag = 1;
			port_number = atoi(optarg);
			break;
		case 'a':
			aflag = 1;
			fprintf(stderr, "Shiqing Liu sliu118.\n");
			exit(1);
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


	if (optind == argc) {
		fprintf(stderr, "Missing mailbox directory.\n");
		exit(1);
	}


	strcpy(directory, argv[optind]);


	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory)) != NULL) {

	    /* find all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {

				string mailbox(ent->d_name);
				mailboxes.insert(mailbox);
			}
		}

		// initialize mutuxes
		for (int i = 0; i < mailboxes.size(); i++) {
			pthread_mutex_init(&locks[i], NULL);
		}

		closedir (dir);

	} else {
	  /* could not open directory */
	  perror ("could not open directory");
	  exit(2);
	}

	struct sigaction act;
	act.sa_handler = signal_handler;
	sigaction(SIGINT, &act, NULL);


	int listen_fd = socket(PF_INET, SOCK_STREAM, 0);

	if (listen_fd < 0) {
		printf("cannot open socket\r\n");
		exit(2);
	}

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(port_number);
	bind(listen_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));

	listen(listen_fd, 10);

	// once you get here, the server is set up and about to start listening
	printf("\nServer configured to listen on port %d\n", port_number);
	fflush(stdout);

	while (true) {

		struct sockaddr_in clientaddr;
		socklen_t clientaddrlen = sizeof(clientaddr);

		int comm_fd = accept(listen_fd, (struct sockaddr*) &clientaddr,
				&clientaddrlen);

		if (comm_fd < 0) {
			close(comm_fd);
			exit(1);
		}

		comm_fd_list.push_back(&comm_fd);

		if (vflag == 1) {
			fprintf(stderr, "[%d] New connection \n", comm_fd);
			fprintf(stderr, "[%d] S: +OK Server ready (Author: Shiqing Liu / sliu118)\r\n", comm_fd);
		}

		pthread_create(&tid[count], NULL, &handle_request, &comm_fd);

		count++;
	}


	close(listen_fd);

	return 0;
}

