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
     * response headers:
     * Set-Cookie
     *
     * entity headers:
     * Content-Length
     * Content-Type
     *
     * */
    std::unordered_map<std::string, std::string> headers;
//    /*
//     * general headers:
//     * Connection
//     * Date
//     * Keep-Alive
//     * */
    /*
     * Content-Length
     * Content-Type
     * */
//    std::unordered_map<std::string, std::string> entity_headers;
    std::string body;
public:

    Response(Request req);
};


#endif //T08_RESPONSE_H
