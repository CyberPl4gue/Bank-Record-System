#include "bank_record.h"

using namespace std;

void bank_record::read_data() {
	cout << "\nEnter Account Number: ";
	cin >> this->account_id;
	cout << "Enter First Name: ";
	cin >> this->firstName;
	cout << "Enter Last Name: ";
	cin >> this->lastName;
	cout << "Enter Balance: ";
	cin >> this->total_Balance;
	cout << endl;
	system("pause");
}
void bank_record::show_data() {
	cout << "Account Number: " << this->account_id << endl;
	cout << "First Name: " << this->firstName << endl;
	cout << "Last Name: " << this->lastName << endl;
	cout << "Current Balance: $" << this->total_Balance << endl;
	cout << "-------------------------------" << endl;
}
void bank_record::write_rec() {
	ofstream outfile;
	outfile.open(this->filename, ios::binary | ios::app);
	if (outfile.is_open()) {
		read_data();
		outfile.write(reinterpret_cast<char*>(this), sizeof(*this));
		outfile.close();
	}
	else {
		cout << "/nError! File " << this->filename << " could not be opened." << endl;
	}
}
void bank_record::read_rec() {
	ifstream infile;
	infile.open(this->filename, ios::binary);
	if (!infile) {
		cout << "/nError! File " << this->filename << " could not be read." << endl;
	}
	cout << "\n****Data from file****" << endl;
	while (!infile.eof())
	{
		if (infile.read(reinterpret_cast<char*>(this), sizeof(*this)))
		{
			show_data();
		}

	}
	system("pause");
	infile.close();
}
void bank_record::search_rec() {
	int n;
	ifstream infile;
	infile.open(this->filename, ios::binary);
	if (!infile)
	{
		cout << "\nError in opening! File Not Found!!" << endl;
		return;
	}
	infile.seekg(0, ios::end);
	int count = infile.tellg() / sizeof(*this);
	cout << "\n There are " << count << " records in the file";
	cout << "\n Enter Record Number to Search: ";
	cin >> n;
	infile.seekg((n - 1) * sizeof(*this));
	infile.read(reinterpret_cast<char*>(this), sizeof(*this));
	show_data();
	system("pause");
}
void bank_record::edit_rec() {
	int n;
	fstream iofile;
	iofile.open(this->filename, ios::binary | ios::in);
	if (!iofile) {
		cout << "/nError in opening! File Not Found!!" << endl;
	}
	iofile.seekg(0, ios::end);
	int count = iofile.tellg() / sizeof(*this);
	cout << "\n There are " << count << " record in the file";
	cout << "\n Enter Record Number to edit: ";
	cin >> n;
	iofile.seekg((n - 1) * sizeof(*this));
	iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
	cout << "Record " << n << " has following data" << endl;
	show_data();
	iofile.close();
	iofile.open(this->filename, ios::out | ios::in | ios::binary);
	iofile.seekp((n - 1) * sizeof(*this));
	cout << "\nEnter data to Modify " << endl;
	read_data();
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void bank_record::delete_rec() {
	int n;
	ifstream infile;
	infile.open(this->filename, ios::binary);
	if (!infile) {
		cout << "/nError in opening! File Not Found!!" << endl;
	}
	infile.seekg(0, ios::end);
	int count = infile.tellg() / sizeof(*this);
	cout << "\n There are " << count << " record in the file";
	cout << "\n Enter Record Number to delete: ";
	cin >> n;
	fstream tmpfile;
	tmpfile.open("tmpfile.bank", ios::out | ios::binary);
	infile.seekg(0);
	for (int i = 0; i < count; i++) {
		infile.read(reinterpret_cast<char*>(this), sizeof(*this));
		if (i == (n - 1)) {
			continue;
		}
		tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
	}
	infile.close();
	tmpfile.close();
	remove("recordsOfFatjonTushe.bank");
	rename("tmpfile.bank", "recordsOfFatjonTushe.bank");
	cout << "Record no." << n << " has been deleted." << endl;
	cout << "-------------------------------" << endl;
	system("pause");
}
