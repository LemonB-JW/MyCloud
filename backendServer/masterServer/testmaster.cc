#include <arpa/inet.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define panic(a...) do { fprintf(stderr, a); fprintf(stderr, "\n"); exit(1); } while (0)
#define logVerbose(a...) do { if (verbose) { struct timeval tv; gettimeofday(&tv, NULL); printf("TST %d.%03d ", (int)tv.tv_sec, (int)(tv.tv_usec/1000)); printf(a); printf("\n"); } } while(0)
#define warning(a...) do { fprintf(stderr, "WARNING: "); fprintf(stderr, a); fprintf(stderr, "\n"); } while (0)

#define MAX_SERVERS 10
#define MAX_CLIENTS 250
#define MAX_MSG_LEN 50
#define MAX_MESSAGES 10000
#define MAX_GROUPS 10

struct {
	int sock;
	bool prime;
	struct sockaddr_in serv_addr;
  in_addr_t ip;
  int port;
} server[MAX_SERVERS];


bool verbose = false;
int numServers;


void readServerList(const char *filename)
{
  FILE *infile = fopen(filename, "r");
  if (!infile)
    panic("Cannot read server list from '%s'", filename);
  char linebuf[1000];
  while (fgets(linebuf, sizeof(linebuf), infile)) {
    char *sproxyaddr = strtok(linebuf, ",\r\n");
    char *srealaddr = sproxyaddr ? strtok(NULL, ",\r\n") : NULL;
    char *serveraddr = srealaddr ? srealaddr : sproxyaddr;
    char *sip = strtok(serveraddr, ":");
    char *sport = strtok(NULL, ":\r\n");
    struct in_addr ip;
    inet_aton(sip, &ip);
    
    struct sockaddr_in temp;
	  bzero((void*)&temp, sizeof(temp));
	  temp.sin_family = AF_INET;
	  inet_aton(sip, &temp.sin_addr);
	  temp.sin_port = htons(atoi(sport));
	  
    if (numServers >= MAX_SERVERS)
      panic("Too many servers defined in '%s' (max %d)", filename, MAX_SERVERS);
    server[numServers].ip = ip.s_addr;
    server[numServers].port = atoi(sport);
    server[numServers].serv_addr = temp;
    numServers ++;
  }
  fclose(infile);
  logVerbose("%d server(s) (including master) found in '%s'", numServers, filename);
}


int main(int argc, char *argv[])
{
  /* Parse arguments */

  int c;
  while ((c = getopt(argc, argv, "o:c:g:m:i:f:v")) != -1) {
    switch (c) {
      case 'v':
        verbose = true;
        break;
      default:
        fprintf(stderr, "Syntax: %s [-v] serverListFile\n", argv[0]);
        exit(1);
    }
  }

  if (optind != (argc-1)) {
    fprintf(stderr, "Error: Name of the server list file is missing!\n");
    return 1;
  }

  readServerList(argv[optind]);


  /* Open client sockets and make each client /join one of the groups */

  for (int i=1; i<numServers; i++) {
    server[i].sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server[i].sock<0)
      panic("Cannot open server socket (%s)", strerror(errno));
		if (connect(server[i].sock, (struct sockaddr *)&server[0].serv_addr, sizeof(server[0].serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    char getPrimeCommand[100];
    sprintf(getPrimeCommand, "GET_PRIME,%d\r\n", i-1);
    send(server[i].sock, getPrimeCommand, strlen(getPrimeCommand), 0); 
    logVerbose("Server %02d sent getprime command to master\n", i-1);
    char buffer[65535];
    int len = read(server[i].sock, buffer, sizeof(buffer));
    
    if (len < 0)
      panic("Cannot read (%s)", strerror(errno));
    fprintf(stderr, "read from master: '%s'", buffer);
    
    char *scomd = strtok(buffer, ",");
    char *spid = strtok(NULL, "\r\n");
    int pid = atoi(spid);
    if (pid == i - 1) {
    	server[i].prime = true;
    }else{
    	server[i].prime = false;
    }
  }
  
  for (int i = 1; i<numServers; i++){
  	if(server[i].prime){
  		char listSubCommand[100];
  		sprintf(listSubCommand, "LIST_SUB,%d\r\n", i-1);
    	send(server[i].sock, listSubCommand, strlen(listSubCommand), 0);
    	logVerbose("Server %02d sent listsub command to master\n", i-1); 
  		char buffer[65535];
    	int len = read(server[i].sock, buffer, sizeof(buffer));
    	if (len < 0)
      	panic("Cannot read (%s)", strerror(errno));
      fprintf(stderr, "read from master: '%s'", buffer);
 
  	}
  }

  return 0;
}
