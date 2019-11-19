#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <unordered_map> 
#include "BigTable.h"
#include "../lib/TableCell.h"


using namespace std;

// PUT(r,c,v): Stores a value v in column c of row r
bool BigTable::put(string row, string col, string* data){
	// write to big table
	if (table.count(row) == 0 || table.count(col) == 0) {
		TableCell* new_cell = new TableCell(data);
		table[row][col] = new_cell;

	} else {
		TableCell* cell = table[row][col];
		delete cell->contents;
		cell->contents = data;
	}

	return true;
}

// GET(r,c): Returns the value stored in column c of row r
string BigTable::get(string row, string col) {
	if (table.count(row) == 0) {
		return "";
	}else{
		if(table[row].count(col) == 0){
			return "";
		}else{
			return *(table[row][col]->contents);			
		}
	}
}

// CPUT(r,c,v1,v2): Stores value v2 in column c of row r, but only if the current value is v1
bool BigTable::cput(string row, string col, string* old_data, string* new_data){
	if (table.count(row) == 0 || table[row].count(col) == 0){
		if (*old_data == "NULL") {
			TableCell* new_cell = new TableCell(new_data);
			table[row][col] = new_cell;
			return true;


		} else {
			return false;
		}
		
	} else {
		TableCell* cell = table[row][col];
		if (*(table[row][col]->contents) == *old_data) {
			delete cell->contents;
			cell->contents = new_data;
			return true;
		} else {
			return false;
		}
	}
}

// DELETE(r,c): Deletes the value in column c of row r
bool BigTable::table_delete(string row, string col){
	if (table.count(row) == 0) {
		return false;
	}else{
		if(table[row].count(col) == 0){
			return false;
		} else {
			delete table[row][col];
			table[row].erase(col);
			return true;
		}
	}
}