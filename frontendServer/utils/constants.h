//
// Created by Xuan Wang on 11/18/19.
//

#ifndef T08_CONSTANTS_H
#define T08_CONSTANTS_H

const static unsigned short MAX_REQUEST_LENGTH = 8192;

const static char *HTTP_VERSION = "HTTP/1.1";
const static char *CONTENT_TYPE = "Content-Type: ";
const static char *CONTENT_LEN = "Content-Length: ";
const static char *COOKIE = "Cookie: ";
const static char *SET_COOKIE = "Set-Cookie: ";
const static char *CONNECTION = "Connection: ";
const static char *STATUS_OK = "200 OK";

const static char *TYPE_HTML = "text/html";
const static char *TYPE_JSON = "application/json";

const static char *CRLF = "\r\n";

const static char *HOME = "/";
const static char *SIGNUP = "/register";
const static char *LOGIN = "/login";
const static char *LOGOUT = "/logout";

const static unsigned short PORT = 8080;
//const static char *STORAGE = "/storage";
const static char *EMAIL = "/email";
//const static char *UPLOAD_URL = "/upload";
//const static char *DOWNLOAD_URL = "/download";
//const static char *NEW_FOLDER_URL = "/newfolder";
//const static char *RENAME_FILE_URL = "/renamefile";
//const static char *DELETE_FILE_URL = "/deletefile";
//const static char *DELETE_FOLDER_URL = "/deletefolder";
//const static char *MOVE_FILE_URL = "/movefile";
const static char *VIEW_EMAIL_URL = "/viewemail";
const static char *SEND_EMAIL_URL = "/compose";    // sending mail
const static char *INBOX = "/inbox";           // mail inbox
//const static char *FORWARD_EMAIL_URL = "/forward";
//const static char *REPLY_EMAIL_URL = "/replyemail";
//const static char *DELETE_EMAIL_URL = "/deleteemail";
//const static char *ADMIN_URL = "/adminconsole";


#endif //T08_CONSTANTS_H
