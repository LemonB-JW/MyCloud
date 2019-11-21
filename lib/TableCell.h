#include <string>
#include <iostream>
#include <pthread.h>

using namespace std;

class TableCell {
public:
	pthread_mutex_t cellMutex;
	string* contents;
	bool onDisk;

	TableCell(string* s) {
		this->contents = s;
		pthread_mutex_init(&cellMutex, NULL);
		onDisk = false;
	}

	TableCell(const TableCell& other) {
		this->contents = other.contents;
		this->onDisk = other.onDisk;
		pthread_mutex_init(&cellMutex, NULL);
	}

	TableCell() {
		pthread_mutex_init(&cellMutex, NULL);
		this->onDisk = false;
		this->contents = NULL;
	}

	~TableCell() {
		delete contents;
	}
};



