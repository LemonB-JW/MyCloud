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

void parse_record(char* buffer, int& priority, char* address){
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



main(int argc, char** argv) {

	unsigned char nsbuf[N];
	char dispbuf[N];
	char address[N];

	ns_msg msg;
	ns_rr rr;
	int i, l;

	if (argc < 2) {
		printf ("Usage: %s <domain>\n", argv[0]);
		exit (1);
	}

    // HEADER
	printf("Domain : %s\n", argv[1]);

    // MX RECORD
	printf("MX records : \n");
	l = res_query(argv[1], C_IN, ns_t_mx, nsbuf, sizeof(nsbuf));
	if (l < 0)
	{
		perror(argv[1]);
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
		exit(EXIT_FAILURE);
	}

/* Host was found. Print its IP address. */
	ip_addr = *(struct in_addr *)(hp->h_addr);
	printf("%s: %s\n",address ,inet_ntoa(ip_addr));

	return 0;
}