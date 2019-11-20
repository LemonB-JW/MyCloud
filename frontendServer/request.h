//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_REQUEST_H
#define T08_REQUEST_H

#include <string.h>
#include <string>

class Request {
    public:
        std::string method;
        std::string req_uri;
//        string version;   // HTTP/1.1
        int content_length;
        std::string cookie;
        std::string header;
//        map<string, string> headers;
//        map<string, string> cookies;
        std::string body;
//        bool valid;

    public:
        Request(int fd);
};
//
//GET /consolke HTTP/1.1
//Host: localhost:8080
//Connection: keep-alive
//        Cache-Control: max-age=0
//Upgrade-Insecure-Requests: 1
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.97 Safari/537.36
//Sec-Fetch-User: ?1
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3
//Sec-Fetch-Site: none
//Sec-Fetch-Mode: navigate
//Accept-Encoding: gzip, deflate, br
//Accept-Language: en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7
//Cookie: Idea-465b027b=dcd70f3e-fe5a-49dd-96b8-c4453861fbee


#endif //T08_REQUEST_H
