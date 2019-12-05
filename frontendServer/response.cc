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

std::string user = "Jill";

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
    MailClient mailClient = setup_mail_client();
    std::vector<MailItem> mail_list = mailClient.requestMailList(user);

    json items;
    for (int i = 0; i < mail_list.size(); i++) {
        MailItem mail = mail_list[i];
        std::string item_name = mail.email_id + mail.from;
        json item = {
                {"item_id", mail.email_id},
                {"from", mail.from},
                {"title", mail.subject},
                {"date", mail.date}
        };
        items[item_name] = item;
    }
    this->headers[CONTENT_TYPE] = TYPE_JSON;
    this->body = items.dump();
    this->headers[CONTENT_LEN] = std::to_string(this->body.length());

    std::cout << items.dump(4) << std::endl;
}

void Response::get_mail_content_handler() {
    MailClient mailClient = setup_mail_client();

    std::string mail_id = "12345";
    std::string mailContent = mailClient.requestMail(user, mail_id);

    this->headers[CONTENT_TYPE] = 



}



void Response::get_drive_list_handler() {

    //TODO: fetch drive list from backend



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

//
//void Response::get_server_list(std::string username) {
//    MasterClient masterClient(
//            grpc::CreateChannel(
//            "127.0.0.1:8001",
//            grpc::InsecureChannelCredentials()
//    )
//    );
//
//    std::string user = "Alice";
//    std::vector<std::string> response = masterClient.getServerList(user);
//    std::cout << "size: " << response.size() << "Servers: " << response[0] << std::endl;
//}

MailClient Response::setup_mail_client()
{
    MailClient client(grpc::CreateChannel(
            "127.0.0.1:4000",
            grpc::InsecureChannelCredentials())
            );
    return client;
}
