#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class bank_records {
private:
	char account_number[20];
	char firstName[10];
	char lastName[10];
	float total_Balance;
public:
	void read_data();
	void show_data();
	void write_rec();
	void read_rec();
	void search_rec();
	void edit_rec();
	void delete_rec();
};

const string filename = "recordsOfFatjonTushe.bank";

int main() {

	int choice;
	bank_records user;
	
	while (true)
	{	
		cout << "***Account Information System***" << endl;
		cout << "Select one option below ";
		cout << "\n\t1-->Add record to file";
		cout << "\n\t2-->Show record from file";
		cout << "\n\t3-->Search Record from file";
		cout << "\n\t4-->Update Record";
		cout << "\n\t5-->Delete Record";
		cout << "\n\t6-->Quit";
		cout << "\nEnter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			user.write_rec();
			break;
		case 2:
			user.read_rec();
			break;
		case 3:
			user.search_rec();
			break;
		case 4:
			user.edit_rec();
			break;
		case 5:
			user.delete_rec();
			break;
		case 6:
			exit(0);
			break;
		default:
			cout << "\nEnter corret choice" << endl;
			system("pause");
		}
		system("cls");
	}
	system("pause");
	return 0;
}

void bank_records::read_data() {
	cout << "\nEnter Account Number: ";
	cin >> account_number;
	cout << "Enter First Name: ";
	cin >> firstName;
	cout << "Enter Last Name: ";
	cin >> lastName;
	cout << "Enter Balance: ";
	cin >> total_Balance;
	cout << endl;
	system("pause");
}
void bank_records::show_data() {
	cout << "Account Number: " << account_number << endl;
	cout << "First Name: " << firstName << endl;
	cout << "Last Name: " << lastName << endl;
	cout << "Current Balance: $" << total_Balance << endl;
	cout << "-------------------------------" << endl;
}
void bank_records::write_rec() {
	ofstream outfile;
	outfile.open(filename, ios::binary | ios::app);
	if (outfile.is_open()) {
		read_data();
		outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
		outfile.close();
	}
	else {
		cout << "/nError! File " << filename << " could not be opened." << endl;
	}
}
void bank_records::read_rec() {
	ifstream infile;
	infile.open(filename, ios::binary);
	if (!infile) {
		cout << "/nError! File " << filename << " could not be read." << endl;
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
void bank_records::search_rec() {
	int n;
	ifstream infile;
	infile.open(filename, ios::binary);
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
void bank_records::edit_rec() {
	int n;
	fstream iofile;
	iofile.open(filename, ios::binary|ios::in);
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
	iofile.open(filename, ios::out | ios::in | ios::binary);
	iofile.seekp((n - 1) * sizeof(*this));
	cout << "\nEnter data to Modify " << endl;
	read_data();
	iofile.write(reinterpret_cast<char*>(this), sizeof(*this ));
}
void bank_records::delete_rec() {
	int n;
	ifstream infile;
	infile.open(filename, ios::binary);
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