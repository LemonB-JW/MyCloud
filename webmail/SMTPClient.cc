string SMTPClient::lookUpIP(string domain) {
	unsigned char nsbuf[N];
	char dispbuf[N];
	char address[N];

	ns_msg msg;
	ns_rr rr;
	int i, l;

    // MX RECORD
	printf("MX records : \n");
	l = res_query(domain.c_str(), C_IN, ns_t_mx, nsbuf, sizeof(nsbuf));
	if (l < 0)
	{
		perror(domain.c_str());
	}
	else
	{

      /* just grab the MX answer info */
		ns_initparse(nsbuf, l, &msg);
		l = ns_msg_count(msg, ns_s_an);
		int priority = INT_MAX;


		for (i = 0; i < l; i++)
		{
			ns_parserr(&msg, ns_s_an, i, &rr);
			ns_sprintrr(&msg, &rr, NULL, NULL, dispbuf, sizeof(dispbuf));
			printf ("\t%s\n", dispbuf);
			parse_record(dispbuf, priority, address);
		}
		std::cout << priority << "\t" << address << std::endl;

	}

	struct hostent *hp;
	struct in_addr ip_addr;

	hp = gethostbyname(address);
	if (!hp) {
		printf("%s not found\n",address);
		return NULL;
		// exit(EXIT_FAILURE);
	}

	/* Host was found. Print its IP address. */
	ip_addr = *(struct in_addr *)(hp->h_addr);
	printf("%s: %s\n",address ,inet_ntoa(ip_addr));

	string IP_address = inet_ntoa(ip_addr);
	string host_ip = IP_address + ":25";

	return host_ip;
}

void SMTPClient::parseRecord(char* buffer, int& priority, char* address) {
	char* token = strtok(buffer, "\t");
	token = strtok(NULL, "\t");
	token = strtok(NULL, "\t");

	char* tok = strtok(token, " ");
	if (priority > atoi(tok)){
		priority = atoi(tok);
		tok = strtok(NULL, " ");
		strcpy(address, tok);
	}
}

void SMTPClient::sendResponse(int fd, string response) {
	if (vflag == 1) {
		fprintf(stderr, "[%d] S: %s", fd, response.c_str());
	}

	write(fd, response.c_str(), strlen(response.c_str()));
}


void SMTPClient::sendCommand(string& domain, string& message, string& sender, string& recipient) {

	// create a new socket
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "Cannot open socket (%s)\n", strerror(errno));
		exit(1);
	}

    // set port for reuse
	const int REUSE = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &REUSE, sizeof(REUSE));


	// parse address and connect to server
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;


	// parse smtp server address
	char* ip = strtok(domain.c_str(),":");
	inet_pton(AF_INET, ip , &servaddr.sin_addr);
	char* port = strtok(NULL,":");
	servaddr.sin_port = htons(atoi(port));

	// source address
	struct sockaddr_in src;
	socklen_t src_size = sizeof(src);


	

}