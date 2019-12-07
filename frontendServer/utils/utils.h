//
// Created by Xuan Wang on 11/17/19.
//
#include <string.h>
#include "../response.h"

/* parse http response object into plain string */
std::string parse_response_to_string(const Response &res);

/* read file content and transfer it to string */
std::string read_file_to_string(std::string filename);

/* get current system time, format is YYYY-MM-DD.HH:mm:ss */
const std::string currentDateTime();


bool do_write(int fd, char *buf, int len);
void termination_handler(int signum);


