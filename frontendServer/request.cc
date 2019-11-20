//
// Created by Xuan Wang on 11/18/19.
//

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
#include "utils/constants.h"
//#include "utils.h"

Request::Request(int fd) {
    char *buf = (char *)malloc(sizeof(char) * MAX_REQUEST_LENGTH);

    read(fd, buf, MAX_REQUEST_LENGTH);
    std::cout << buf << std::endl;

    std::string request = std::string(buf);
    

    if (buf != NULL) {
        free(buf);
    }

}

