#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

class bank_record {
private:
	char account_id[20];
	char firstName[10];
	char lastName[10];
	float total_Balance;
	const char filename[26] = "recordsOfFatjonTushe.bank";
public:
	void read_data();
	void show_data();
	void write_rec();
	void read_rec();
	void search_rec();
	void edit_rec();
	void delete_rec();
};

