#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_set>

#include "request.h"
#include "response.h"
#include "utils/utils.h"
#include "utils/constants.h"
//#include <experimental/filesystem>

using namespace std;
//namespace fs = std::experimental::filesystem;

#define debug(a...) do { if (verbose) fprintf(stderr, a); } while (0)

/* enter debug mode if verbose = true */
bool verbose = false;
/* port number if port is specified by -p */
int port;



void *worker(void *arg)
{
    int comm_fd = *(int *)arg;

    // parse incoming http request into structured request object
    Request req(comm_fd);
    Response res(req);

    // parse Response object into c-style byte array
    string res_str = parse_response_to_string(res);
    char *response = (char *)res_str.c_str();

    // write to fd
    do_write(comm_fd, response, strlen(response));

    // debug mode
    debug("[%d] S: %s", comm_fd, response);
    debug("[%d] S: %s", comm_fd, "Connection closed\n");

    close(comm_fd);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    if (argc < 1)
    {
        fprintf(stderr, "Something went wrong!\n");
        exit(1);
    }

    int pflag = 0; // indicate if "-p" is specified
    int aflag = 0; // indicate if "-a" is specified
    char *pValue = NULL;
    int c;

    opterr = 0;

    /* parse optional argument n */

    while ((c = getopt(argc, argv, "avp:")) != -1)
    {
        switch (c)
        {
            case 'a':
                fprintf(stderr, "Full Name: Xuan Wang, seas login: xuanw \n");
                aflag = 1;
                exit(0);
            case 'v':
                verbose = true;
                break;
            case 'p':
                pflag = 1;
                pValue = optarg;
                port = atoi(pValue);
                break;
            case '?':
                if (optopt == 'p')
                    fprintf(stderr, "Option -%c has an argument %d.\n", optopt, c);
                return 1;
            default:
                abort();
        }
    }

    /* connection setup */
    int listen_fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 100);

    puts("here!");

    while (true)
    {
        puts("here2!");

        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        int *fd = (int *)malloc(sizeof(int));
        *fd = accept(listen_fd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        printf("[%d] New Connection %s\n", *fd, inet_ntoa(clientaddr.sin_addr));

        pthread_t thread;
        pthread_create(&thread, NULL, worker, fd);
    }

    return 0;
}
