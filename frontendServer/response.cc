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
#include "utils/utils.h"

Response::Response(Request req) {
    std::cout << "response " << req.method;
    char *filename = "html/compose.html";
    std::string content = read_file_to_string(filename);
    this->http_version = HTTP_VERSION;
    this->status_code = STATUS_OK;
    this->headers[CONTENT_LEN] = std::to_string(content.length());
    this->headers[CONTENT_TYPE] = TYPE_HTML;
    this->body = content;
}
