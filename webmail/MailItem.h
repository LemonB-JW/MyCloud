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
	std::string email_id;

public:
	// constructor
	MailItem(std::string from, std::string subject, std::string date, std::string email_id) : from(from), subject(subject), date(date), email_id(email_id) {};

	// deconstructor
	~MailItem() {};


};

