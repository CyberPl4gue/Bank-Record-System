#include <iostream>
#include "bank_record.h"

using namespace std;

int main() {

	int choice;
	bank_record user;
	
	while (true)
	{	
		cout << "***Account Information System***" << endl;
		cout << "Select one option below ";
		cout << "\n\t1) Add record to file";
		cout << "\n\t2) Show record from file";
		cout << "\n\t3) Search Record from file";
		cout << "\n\t4) Update Record";
		cout << "\n\t5) Delete Record";
		cout << "\n\t6) Quit";
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