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

public:
	// constructor
	MailItem(std::string from, std::string subject, std::string date) : from(from), subject(subject), date(date) {};

	// deconstructor
	~MailItem() {};


};

