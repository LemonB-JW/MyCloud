//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_RESPONSE_H
#define T08_RESPONSE_H

#include <string.h>
#include <string>
#include <unordered_map>

#include "request.h"


class Response {
public:
    std::string http_version;
    std::string status_code;
    /*
     * headers:
     * Set-Cookie
     *
     * entity headers:
     * Content-Length
     * Content-Type
     *
     * */
    std::unordered_map<std::string, std::string> headers;
    std::string body;
    bool isJSON;

public:
    Response(Request req);

public:
    void parse_req_string(Request &req, std::string req_str);
};


#endif //T08_RESPONSE_H
