//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_RESPONSE_H
#define T08_RESPONSE_H

#include <string.h>
#include <string>
#include <unordered_map>
#include <json.hpp>

#include "request.h"

using json = nlohmann::json;

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

public:
    Response(Request req);

public:
    void parse_req_string(Request &req, std::string req_str);
    void get_inbox_list_handler();
    void get_drive_list_handler();
    void get_html_handler(std::string &url);


    /* write JSON object to HTTP response */
//    void write_json_to_response(Response &res, json json_obj);

};


#endif //T08_RESPONSE_H
