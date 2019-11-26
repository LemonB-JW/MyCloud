#include <string>
#include <iostream>

using namespace std;

class TableCell {
public:
	string* contents;
	bool onDisk;

	TableCell(string* s) {
		this->contents = s;
		onDisk = false;
	}

	TableCell(const TableCell& other) {
		this->contents = other.contents;
		this->onDisk = other.onDisk;
	}

	TableCell() {
		this->onDisk = false;
		this->contents = NULL;
	}

	~TableCell() {
		delete contents;
	}
};



