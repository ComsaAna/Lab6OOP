// lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <Windows.h>
#include <atlstr.h>
#include "Controller.cpp"
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

void Teste() {
	Controller cont;
	cont.repo.create_list();
	assert(cont.repo.length == 10);
	assert(cont.repo.wlen == 0);
	Movie m1("a", "a", 2000, 10, "https://www.google.ro/?gws_rd=ssl");
	Movie m2("b", "b", 2001, 9, "https://www.youtube.com/");
	cont.repo.add_movie(m1, "admin");
	cont.repo.add_movie(m2, "admin");
	assert(cont.repo.length == 12);
	cont.repo.add_movie(m1, "user");
	cont.repo.add_movie(m2, "user");
	assert(cont.repo.wlen == 2);
	cont.repo.delete_movie_watchlist("a", 2000);
	assert(cont.repo.wlen == 1);
	cont.repo.delete_movie_list("b", 2001);
	assert(cont.repo.length == 11);
}

int main()
{
	// Teste();
	Controller cont;
	cont.repo.create_list();
	CString url;
	string mode, genre, title;
	int option, year, likes;
	cout << "WELCOME! \n";
	cout << endl << "Bored in the house? Well now you're in the right place! Let's get it started!" << endl << "You can..." << endl;

	while (true) {
		cout << "\nChoose a mode:" << endl << "User/Admin: ";
		cin >> mode;
		if (mode == "User") {
			cout << endl << "You entered the User mode" << endl;
			while (true) {
				cout << endl << "1. Search movies by genre and add some in your watchlist" << endl << \
					"2. Delete the movie you already saw" << endl << \
					"3. See your watchlist" << endl << \
					"4. See all movies" << endl << \
					"5. Back" << endl << \
					"6. Exit";
				cout << endl << "Your option: ";
				cin >> option;
				//Uberpruft ob die Option ein Integer ist = Datenvalidierung
				while (cin.fail()) {
					cout << "Please type a valid option" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cout << endl << "Your option: ";
					cin >> option;
				}
				if (option == 1) {
					cout << endl << "Search movies" << endl << "Some ideas for genre: SF, comedy, drama, action, mystery, thriller..." << endl << \
						"Hint: If you didn't think of a specific genre, just type '?', and you'll see the entire list of movies" << endl;
					cout << "Genre: ";
					cin >> genre;
					cont.find_movie(genre);
				}
				else if (option == 2) {
					cout << endl << "Delete movies" << endl << \
						"Hint: If you watched the movie and want to delete it from the watchlist, just type its name and year" << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					cout << "Year: ";
					cin >> year;
					//Uberpruft ob das Jahr gultig ist = Datenvalidierung
					while (cin.fail() || year < 1800 || year>2020) {
						cout << endl << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> year;
					}
					cont.repo.delete_movie_watchlist(title, year);
				}
				else if (option == 3) {
					cout << endl << "Your watchlist:" << endl;
					cont.show_watchlist();
					cout << endl;
				}
				else if (option == 4) {
					cout << endl << "All movies:" << endl;
					cont.repo.show_movies();
					cout << endl;
				}
				else if (option == 5) {
					cout << "\nYou want to switch the mode from user to administrator.\nNow you can choose again!\n";
					break;
				}
				else if (option == 6) {
					cout << endl << "So you're not bored anymore, great! We'll see you next time!" << endl;
					return 0;
				}
				else {
					cout << endl << "Please type a valid option!" << endl;
				}
			}
		}

		else if (mode == "Admin") {
			cout << endl << "You entered the Administrator mode" << endl;
			while (true) {
				cout << endl << "1. Add a new movie to the movielist" << endl << \
					"2. Delete a movie from the movielist" << endl << \
					"3. Edit a movie" << endl << \
					"4. See the movielist" << endl << \
					"5. Back" << endl << \
					"6. Exit";
				cout << endl << "Your option: ";
				cin >> option;
				//Uberpruft ob die Option ein Integer ist = Datenvalidierung
				while (cin.fail()) {
					cout << "Please type a valid option" << endl;
					cin.clear();
					cin.ignore(256, '\n');
					cout << endl << "Your option: ";
					cin >> option;
				}
				if (option == 1) {
					cout << endl << "Add a movie";
					cout << "\nTitle: ";
					cin.get();
					getline(cin, title, '\n');
					cout << "Genre: ";
					cin >> genre;
					cout << "Year: ";
					cin >> year;
					//Uberpruft ob das Jahr gultig ist = Datenvalidierung
					while (cin.fail() || year < 1800 || year>2020) {
						cout << endl << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> year;
					}
					cout << "Likes: ";
					cin >> likes;
					//Uberpruft ob das Jahr gultig ist = Datenvalidierung
					while (cin.fail()) {
						cout << endl << "Please enter a valid number of Likes" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> likes;
					}
					cout << "Trailer: ";
					char myString[256];
					cin >> myString;
					url = CString(myString);
					Movie m(title, genre, year, likes, url);
					cont.repo.add_movie(m, "admin");
				}
				else if (option == 2) {
					cout << endl << "Delete movies" << endl << \
						"Hint: If you don't like the movie, you can delete it." << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					cout << "Year: ";
					cin >> year;
					//Uberpruft ob das Jahr gultig ist = Datenvalidierung
					while (cin.fail() || year < 1800 || year>2020) {
						cout << endl << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> year;
					}
					cont.repo.delete_movie_list(title, year);
				}
				else if (option == 3) {
					string edit_opt;
					cout << endl << "Edit movies" << endl << \
						"You can choose between these edit options: title, genre, year, likes, trailer" << endl;
					cout << "Title: ";
					cin.get();
					getline(cin, title, '\n');
					cout << "Year: ";
					cin >> year;
					//Uberpruft ob das Jahr gultig ist = Datenvalidierung
					while (cin.fail() || year < 1800 || year>2020) {
						cout << endl << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> year;
					}
					cout << "Option: ";
					cin >> edit_opt;
					cont.repo.edit_movie(title, year, edit_opt);
				}
				else if (option == 4) {
					cout << endl << "Your Movielist:" << endl;
					cont.repo.show_movies();
					cout << endl;
				}
				else if (option == 5) {
					cout << "\nYou want to switch the mode from administrator to user.\nNow you can choose again!\n";
					break;
				}
				else if (option == 6) {
					cout << endl << "So you're not bored anymore, great! We'll see you next time!" << endl;
					return 0;
				}
				else {
					cout << endl << "Please type a valid option!" << endl;
				}
			}
		}
		else {
			cout << "Please choose a valid mode" << endl;
		}
	}
	return 0;
}