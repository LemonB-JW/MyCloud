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

#include "constants.h"
//#include "../response.h"
#include "utils.h"

using namespace std;

// This macros will check the verbose status. It makes sure only outputting log
// when it is turned on



pthread_mutex_t write_mutex;

unordered_set<string> stringSet;

int vflag = 0; // indicate if "-v" is specified

struct Buffer_smtp
{
    char *data;
    char *sender;
    vector<string> receivers;
};

// define state order to maintain state machine, HELO = 1, MAIL = 2, RECV = 3, DATA = 4 ...
enum command_state
{
    NONE,
    HELO,
    HELO_AGAIN,
    MAIL,
    RCPT,
    DATA,
    RSET,
    QUIT
};


string dir;

/* parse http response object into plain string */
string parse_response_to_string(const Response &res) {
//    if (res.isJSON) {
//        return res.body;
//    }
    string status_line = res.http_version + " " + res.status_code + CRLF;
    string headers;

    // iterate over map headers and keep appending
    auto it = res.headers.begin();
    while (it != res.headers.end())
    {
        std::string key = it->first;
        std::string val = it->second;

        headers += (key + val) + CRLF;
        // Increment the Iterator to point to next entry
        it++;
    }

    // create http response string
    string res_str = status_line + headers + CRLF + res.body + CRLF;

    return res_str;
}


/* read file content and transfer it to string */
string read_file_to_string(string filename) {
    ifstream file(filename);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

/* iterate over the given directory and save user names in a hashset */
void save_users(string path) {
//{
//    for (const auto &entry : fs::directory_iterator(path))
//    {
//        int len = path.length() + 1;
//        string filepath = string(entry.path()).substr(len);
//        string username = filepath.substr(0, filepath.find("."));
//        stringSet.insert(username);
//    }
}

// check if data is ended with "<CR><LF>.<CR><LF>"
bool check_data_end(char *buf)
{
    int len = strlen(buf);
    if (len >= 5 && buf[len - 5] == '\r' && buf[len - 4] == '\n' && buf[len - 3] == '.' && buf[len - 2] == '\r' && buf[len - 1] == '\n')
    {
        return true;
    }
    return false;
}

bool validate_string(string s, char *response, string flag) {
//    vector <string> tokens;         // Vector of string to save tokens
//    stringstream stream(s);        // stringstream class stream
//    string intermediate;
    bool isTrue = true;
//
//    while(getline(stream, intermediate, ' '))
//    {
//        tokens.push_back(intermediate);
//    }
//    // # of arguments
//    if (tokens[0] == "\r\n" || tokens.size() > 1 || tokens.size() == 0) {   // "HELO \r\n"  OR  "HELO A B C\r\n"
//        strcpy(response, res_err_domain);
//        isTrue = false;
//    }
//    if (flag == "helo") {
//        return isTrue;
//    }
//    string address = tokens[0];   //  <a@localhost>
//    int pos = address.find("@") + 1;
//    if (pos - 1 == string::npos) {
//        strcpy(response, res_err_domain);
//        isTrue = false;
//    }
    return isTrue;
}

///* write message to file */
//int write_file(string filename, char *input)
//{
//    char *path = (char*)filename.c_str();
//    FILE* fp = fopen(path, "a");
//
//    if(fp) {
//        fputs(input, fp);
//        fclose(fp);
//    }
//}

bool do_write(int fd, char *buf, int len)
{
    int sent = 0;
    while (sent < len)
    {
        int n = write(fd, &buf[sent], len - sent);
        if (n < 0)
        {
            return false;
        }
        sent += n;
    }
    return true;
}

//
//
//bool read_line_by_line() {
//    char *buf = malloc(sizeof(char) * MAX_REQUEST_LENGTH);
//    char full_line[1024];
//
//    read(comm_fd, buf, MAX_REQUEST_LENGTH);
//    cout << buf << endl;
//
//
//    int rcvd = 0; // rcvd to mark the next position of last received character in previous round
//    unsigned short rlen;
//    bool isQuit = false; // if "Quit" is caught, isQuit is set to true
//    bool isEnd = false;
//
//    while (!isQuit) {
//        rlen = read(comm_fd, buf + rcvd, 1024);
//
//        // check if contains "\r\n"
//        int new_head = 0;
//        int cur_start = 0;
//        for (int i = rcvd; i < rcvd + rlen; i++) {
//            if (i > 1 && buf[i] == '\n' && buf[i - 1] == '\r') {
//                // clean contents left in full_line
//                memset(full_line, '\0', 1024);
//                strncpy(full_line, buf + cur_start, i + 1 - cur_start);
//                // debug mode
//                if (vflag == 1) {
//                    fprintf(stderr, "[%d] C: %s", comm_fd, full_line);
//                }
//                // process the commands and return correct response to be written to client
//                response_handler(response, full_line, &isQuit, &state, &buff_smtp);
//                if (strlen(response) != 0) {
//                    do_write(comm_fd, response, strlen(response));
//                    // debug mode
//                    if (vflag == 1) {
//                        fprintf(stderr, "[%d] S: %s", comm_fd, response);
//                    }
//                }
//
//                // mark the end of current command
//                isEnd = true;
//
//                // update start of current line
//                cur_start = i + 1;
//                new_head = 0;
//
//                // check data end
//                if (state == DATA && check_data_end(buff_smtp.data)) {
//                    state = HELO_AGAIN; // return to state after "HELO"
//                    int i = strlen(buff_smtp.data) - 1;
//                    buff_smtp.data[i - 2] = '\0'; // remove .<CR><LF>
//
//                    // get current time and create a header message for each mail
//                    time_t now = time(0);
//                    char *dt = ctime(&now);
//                    char header[256];
//                    strcpy(header, "From ");
//                    strcpy(header + 5, buff_smtp.sender);
//                    strcpy(header + strlen(header), " ");
//                    strcpy(header + strlen(header), dt);
//
//                    // send data to all recipients
//                    // lock file to be written
//                    pthread_mutex_lock(&write_mutex);
//                    for (int i = 0; i < buff_smtp.receivers.size(); i++) {
//                        string destination = dir + buff_smtp.receivers[i] + ".mbox";
//                        write_file(destination, header);
//                        write_file(destination, buff_smtp.data);
//                    }
//                    pthread_mutex_unlock(&write_mutex);
//
//                    // clear all buffers
//                    memset(buff_smtp.data, '\0', strlen(buff_smtp.data));
//                    memset(buff_smtp.sender, '\0', strlen(buff_smtp.sender));
//                    buff_smtp.receivers.clear();
//
//                    strcpy(response, res_succ_OK);
//                    do_write(comm_fd, response, strlen(response));
//                    if (vflag == 1) {
//                        fprintf(stderr, "[%d] S: %s", comm_fd, response);
//                    }
//                }
//                continue;
//            }
//            // Copy the characters left to the head of buffer
//            if (isEnd) {
//                buf[new_head++] = buf[i];
//            }
//        }
//
//        if (!isEnd) {
//            rcvd += rlen;
//        } else {
//            rcvd = new_head;
//            memset(buf + rcvd, '\0', sizeof(buf));
//        }
//        isEnd = false;
//    }
//}
