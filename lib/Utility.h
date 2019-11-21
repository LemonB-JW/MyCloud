#ifndef UTILITY_H_ 
#define UTILITY_H_
#include <string.h>
using namespace std;

class Utility
{

public:
	static string generateFileID(int worker_index, int sequence_num);
};

#endif