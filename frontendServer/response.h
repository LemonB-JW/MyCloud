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
    std::unordered_map<std::string, std::string> headers;
    std::string body;
public:
    Response(Request req);
};


#endif //T08_RESPONSE_H
