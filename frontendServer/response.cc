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

Response::Response(const Request& req) {

    std::string url = req.req_uri;
    std::string content;

    if (req.method == "GET") {
        if (url == "/inbox_items") {
            get_inbox_list_handler();
        } else if (url.find("/drive_items") == 0) {
            int pos = url.find("/drive_items");
            pos = url.find("/", pos + 1);
            std::string path = url.substr(pos + 1, url.length() - pos);  //TODO: sanity check
//            std::cout << "drive path: " << path << std::endl;

            get_drive_list_handler(path);
        } else if (url == "/mail_item") {
            get_mail_content_handler();
        }
        else {
            get_html_handler(url);
        }
    } else if (req.method == "POST"){

        std::cout << "method : " << req.method << std::endl;
        std::cout << "Json: " << req.body.dump() << std::endl << req.body["name"] << std::endl;

    }

    this->http_version = HTTP_VERSION;
    this->status_code = STATUS_OK;
}

/*
 * fetch designated inbox mail list by user
 * */
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
}

/*
 * fetch designated mail content by mail_id and user
 * */
void Response::get_mail_content_handler() {
    MailClient mailClient = setup_mail_client();

    std::string mail_id = "12345";
    std::string mailContent = mailClient.requestMail(user, mail_id);

    json item = {
            {"mail_content", mailContent}
    };

    this->headers[CONTENT_TYPE] = TYPE_JSON;
    this->body = item.dump();
    this->headers[CONTENT_LEN] = std::to_string(this->body.length());

    std::cout << item.dump(4) << std::endl;
}



void Response::get_drive_list_handler(std::string &path) {
    TableClient tableClient = setup_table_client();
    std::vector<FileMetaData> files_data = tableClient.list_all_files(user, path);

    std::cout << "size: " << files_data.size() << std::endl;

    //TODO: fetch drive list from backend
//    json items;
//    for (int i = 0; i < files_data.size(); i++) {
//        FileMetaData file = files_data[i];
//        std::string item_name = file.file_id + file.created_time;
//        json item = {
//                {"file_id", file.file_id},
//                {"file_type", file.file_type},  // "folder" or "email" or "file"
//                {"name", file.file_name},
//                {"owner", file.file_from},
//                {"created_time", file.created_time}
//        };
//        items[item_name] = item;
//    }

    int num_of_items = 3;
    json items;
    for (int i = 0; i < num_of_items; i++) {
        std::string item_name = "item" + std::to_string(i);
        json item = {
                {"file_id", std::to_string(10)},
                {"file_type", "file"},
                {"name", "foo.txt"},
                {"owner", "Janice"},
                {"created_time", "2019 11 21"}
        };
        items[item_name] = item;
    }

    std::string item_name = "item" + std::to_string(10);
    json item = {
            {"file_id", std::to_string(10)},
            {"is_folder", "folder"},
            {"name", "foo.txt"},
            {"owner", "Janice"},
            {"modify_date", "2019 11 21"}
    };
    items[item_name] = item;


    this->headers[CONTENT_TYPE] = TYPE_JSON;
    this->body = items.dump();
    this->headers[CONTENT_LEN] = std::to_string(this->body.length());
}

/*
 * load html pages initially
 * */
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



TableClient Response::setup_table_client() {
    TableClient client(grpc::CreateChannel(
            "127.0.0.1:5003",
            grpc::InsecureChannelCredentials())
    );
    return client;
}