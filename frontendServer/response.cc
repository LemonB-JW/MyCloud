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
#include <json.hpp>

using json = nlohmann::json;

Response::Response(Request req) {

    std::string url = req.req_uri;
    std::string content;

    if (req.method == "GET") {
        if (url == "/inbox_items") {
            get_inbox_list_handler();

        } else if (url == "/drive_items") {
            get_drive_list_handler();
        }

        else {
            get_html_handler(url);
        }
    } else if (req.method == "POST") {

    }

    this->http_version = HTTP_VERSION;
    this->status_code = STATUS_OK;
}

void Response::get_inbox_list_handler() {
    int num_of_items = 3;
    json items;
    for (int i = 0; i < num_of_items; i++) {
        std::string item_name = "item" + std::to_string(i);
        json item = {
                {"item_id", std::to_string(i)},
                {"from", "Xuan"},
                {"title", "Project Report - T08"},
                {"date", "2019 11 20"}
        };
        items[item_name] = item;
    }
    this->headers[CONTENT_TYPE] = TYPE_JSON;
    this->body = items.dump();
    this->headers[CONTENT_LEN] = std::to_string(this->body.length());

    std::cout << items.dump(4) << std::endl;
}

void Response::get_drive_list_handler() {
    int num_of_items = 3;
    json items;
    for (int i = 0; i < num_of_items; i++) {
        std::string item_name = "item" + std::to_string(i);
        json item = {
                {"item_id", std::to_string(i)},
                {"is_folder", true},
                {"name", "Project Report - T08"},
                {"modify_date", "2019 11 20"}
        };
        items[item_name] = item;
    }
    this->headers[CONTENT_TYPE] = TYPE_JSON;
    this->body = items.dump();
    this->headers[CONTENT_LEN] = std::to_string(this->body.length());

    std::cout << items.dump(4) << std::endl;
}

void Response::get_html_handler(std::string &url) {
    // add html file into response body
    std::string filename = "html" + url + ".html";
    std::cout << filename << std::endl;
    std::string content = read_file_to_string(filename);
    this->headers[CONTENT_TYPE] = TYPE_HTML;
    this->body = content;
    this->headers[CONTENT_LEN] = std::to_string(content.length());
}

