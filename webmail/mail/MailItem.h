#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>

class MailItem
{

public:
	std::string from;
	std::string subject;
	std::string date;
	std::string content;

public:
	// constructor
	MailItem(std::string from, std::string subject, std::string date, std::string content) : from(from), 
	subject(subject), date(date), content(content) {};

	// deconstructor
	~MailItem() {};


};

