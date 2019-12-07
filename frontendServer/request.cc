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
    std::string request = std::string(buf);
//    std::cout << request<< std::endl;
    parse_req_string(*this, request);
    std::cout << this->method << std::endl;
    this->cookie = headers["Cookie"];

    if (buf != NULL) {
        free(buf);
    }
}

/* parse incoming request string into structured request object */
void Request::parse_req_string(Request &req, std::string req_str) {

    // parse json data in post request if any
    std::string copy = req_str;
    int data_start = copy.rfind("{");
    int data_end = copy.rfind("}");

    if (data_start >= 0) {
        std::string data = copy.substr(data_start, data_end - data_start + 1);
        auto json_data = json::parse(data);
        req.body = json_data;

        req_str = req_str.substr(0, data_start);
    }

    size_t pos, prior_pos;

    // 1. parse start line: method, url, http version
    pos = req_str.find(" ");
    req.method = req_str.substr(0, pos);
    prior_pos = pos;

    pos = req_str.find(" ", prior_pos + 1);
    req.req_uri = req_str.substr(prior_pos + 1, pos - prior_pos - 1);
    prior_pos = pos;

    pos = req_str.find(CRLF, prior_pos + 1);
    req.version = req_str.substr(prior_pos + 1, pos - prior_pos - 1);
    prior_pos = pos;

    std::string headers = req_str.substr(prior_pos + 1, req_str.length() - prior_pos);

    // 2. parse headers
    prior_pos = 0;  // reset prior_pos
    while (pos >= headers.length() || pos != std::string::npos) {
        pos = headers.find(":", prior_pos + 1);
        std::string key = headers.substr(prior_pos + 1, pos - prior_pos - 1);
        prior_pos = pos;

        if (pos >= headers.length()) {
            break;
        }

        pos = headers.find("\n", prior_pos + 1);
        std::string val = headers.substr(prior_pos + 2, pos - prior_pos - 3);
        prior_pos = pos;

        req.headers[key] = val;
    }
}


