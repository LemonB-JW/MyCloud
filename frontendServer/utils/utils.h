//
// Created by Xuan Wang on 11/17/19.
//
#include <string.h>
#include "../response.h"

bool do_write(int fd, char *buf, int len);
void termination_handler(int signum);
std::string get_file_content_as_string(const char *filename);
std::string parse_response_to_string(const Response &res);


