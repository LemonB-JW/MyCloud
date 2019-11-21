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

//
//GET /consolke HTTP/1.1
//Host: localhost:8080
//Connection: keep-alive
//        Cache-Control: max-age=0
//Upgrade-Insecure-Requests: 1
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36
//Sec-Fetch-User: ?1
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3
//Sec-Fetch-Site: none
//Sec-Fetch-Mode: navigate
//Accept-Encoding: gzip, deflate, br
//Accept-Language: en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7
//Cookie: Idea-465b027b=dcd70f3e-fe5a-49dd-96b8-c4453861fbee

Request::Request(int fd) {
    char *buf = (char *)malloc(sizeof(char) * MAX_REQUEST_LENGTH);

    read(fd, buf, MAX_REQUEST_LENGTH);
    std::cout << "REQUEST: " <<  buf << std::endl;

    std::string request = std::string(buf);
    parse_req_string(*this, request);

    

    if (buf != NULL) {
        free(buf);
    }
}

/* parse incoming request string into structured request object */
void Request::parse_req_string(Request &req, std::string req_str) {

    size_t pos = req_str.find(CRLF);
//    std::string start_line = req_str.substr(0, pos);

    size_t prior_pos;

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

    // 2. parse headers
    while (pos <= req_str.length()) {
        pos = req_str.find(":", prior_pos + 1);
        std::string key = req_str.substr(prior_pos + 1, pos - prior_pos);
        prior_pos = pos;

        pos = req_str.find("CRLF", prior_pos + 1);
        std::string val = req_str.substr(prior_pos + 1, pos - prior_pos);
        prior_pos = pos;

        req.headers[key] = val;
    }
}


