#ifndef UTILITY_H_ 
#define UTILITY_H_
#include <string.h>
using namespace std;

class Utility
{

public:
	static string generateFileID(string path_name);
	static string parseFileName(string path_name);
};

#endif