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
            isJSON = true;

            int num_of_items = 2;
            json items;

            for (int i = 0; i < num_of_items; i++) {
                std::string item_name = "item" + std::to_string(i);
                json item = {
                        {"item_id", std::to_string(i)},
                        {"from", "Xuan"},
                        {"title", "THIS IS TITLE"},
                        {"date", "2019 11 20"}
                };
                items[item_name] = item;
            }
            content = items.dump();
            this->headers[CONTENT_TYPE] = TYPE_JSON;

//            std::cout << items.dump(4) << std::endl;

        } else if (url == "/drive_items") {

//        } else if () {

        }
        else {
            // add html file into response body
            std::string filename = "html" + url + ".html";
            std::cout << filename << std::endl;
            content = read_file_to_string(filename);
            this->headers[CONTENT_TYPE] = TYPE_HTML;
        }
    } else if (req.method == "POST") {

    }

    this->http_version = HTTP_VERSION;
    this->status_code = STATUS_OK;

    if (content != "") {
        this->headers[CONTENT_LEN] = std::to_string(content.length());
        this->body = content;
    }

}

//bool Response::need_html(string url) {
//    if (url == SEND_EMAIL_URL || url == LOGIN || url == INBOX || )
//}
