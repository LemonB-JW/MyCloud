//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_RESPONSE_H
#define T08_RESPONSE_H

#include <string.h>
#include <string>
#include <unordered_map>
#include <json.hpp>
#include "../webmail/MailClient.h"
#include "TableClient.h"
#include "mail.grpc.pb.h"

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
    void get_mail_content_handler();
    void send_mail_handler();

    void get_drive_list_handler(std::string &path);
    void download_drive_file_handler();
    void upload_drive_file_handler();
    void create_drive_folder_handler(std::string name);
    void move_drive_file_handler(std::string oldpath, std::string newpath, std::string type);
    void rename_drive_file_handler(std::string oldname, std::string newname, std::string type);
    void delete_drive_file_handler(std::string path, std::string type);


    void get_html_handler(std::string &url);
    void get_server_list(std::string username);

private:
    MailClient setup_mail_client();
    TableClient setup_table_client();



        /* write JSON object to HTTP response */
//    void write_json_to_response(Response &res, json json_obj);

};


#endif //T08_RESPONSE_H
