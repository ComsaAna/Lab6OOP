#include <iostream>

using namespace std;

class Exceptions {
public:
	Exceptions() {

	}

	bool LikeExcept(int &likes) {
		try {
			cout << "Likes= ";
			cin >> likes;
		}
		catch(...) {
			cout << "\nOh no...An exception occured. Please enter a valid number of Likes\n";
			return false;
		}
		return true;
	}

	bool YearExcept(int &year) {
		try {
			cout << "Year= ";
			cin >> year;
		}
		catch (...) {
			cout << "\nOh no...An exception occured. Please enter a valid year\n";
			return false;
		}
		return true;
	}

	bool OptionExcept(int &option) {
		try {
			cout << "Your option= ";
			cin >> option;
		}
		catch (...) {
			cout << "\nOh no...An exception occured. Please type a valid option\n";
			return false;
		}
		return true;
	}
};