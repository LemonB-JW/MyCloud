//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_REQUEST_H
#define T08_REQUEST_H

#include <string.h>
#include <string>
#include <unordered_map>

class Request {
public:
    std::string method;
    std::string req_uri;
    std::string version;   // HTTP/1.1
    std::string cookie;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
//        bool valid;
    int content_length;


public:
    Request(int fd);

private:
    void parse_req_string(Request &req, std::string req_str);


};

#endif //T08_REQUEST_H
