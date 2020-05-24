#include <iostream>
#include "Ausnahmen.cpp"

using namespace std;

class Validation {
public:
	Exceptions valid;

public:
	Validation() {
	}
	void ValidYear(int &year) {
		//Uberpruft ob das Jahr gultig ist = Datenvalidierung
		while (!valid.YearExcept(year) || year < 1800 || year>2020) {
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	void ValidLikes(int &likes) {
		cout << "Likes: ";
		cin >> likes;
		//Uberpruft ob das Jahr gultig ist = Datenvalidierung
		while (!valid.LikeExcept(likes) || likes < 0) {
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	void ValidOption(int &option) {
		//Uberpruft ob die Option ein Integer ist = Datenvalidierung
		while (!valid.OptionExcept(option) || option <= 0 || option >= 7) {
			cin.clear();
			cin.ignore(256, '\n');
		}
	}

	int ValidMode(string mode) {
		if (mode == "user" || mode == "User") {
			return 1;
		}
		if (mode == "Admin" || mode == "admin") {
			return 2;
		}
		return 0;
	}
};