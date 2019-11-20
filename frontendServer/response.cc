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

#include "response.h"
#include "utils/constants.h"

Response::Response(Request req) {
    std::cout << "response " << req.method;

    this->http_version = HTTP_VERSION;
    this->status_code = "200 OK";
}
