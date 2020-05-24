#include "Domain.cpp"
#include <iostream>
using namespace std;

class Repo {
public:
	Movie movies[100];
	Movie watchlist[100];
	int length = 10;
	int wlen = 0;

	Repo() {

	};

	Movie* create_list() {
		// die Datenbank erstellen
		string titles[10] = { "Suicide Squad", "Titanic", "Pirates of the Caribbean", "Murder on the orient express", "Avatar", "The professor", "Dead Poets Society", "Frozen", "Joker", "The Giver" };
		string genres[10] = { "action", "drama", "action", "mystery", "SF", "comedy", "drama", "animation", "thriller", "SF" };
		int years[10] = { 2016, 1997, 2017, 2017, 2009, 2018, 1989, 2013, 2019, 2014 };
		int likes[10] = { 10, 11, 9, 8, 7, 7, 10, 8, 9, 11 };
		CString trailers[10] = { "https://www.youtube.com/watch?v=CmRih_VtVAs", "https://www.youtube.com/watch?v=2e-eXJ6HgkQ", "https://www.youtube.com/watch?v=naQr0uTrH_s", \
			"https://www.youtube.com/watch?v=Mq4m3yAoW8E", "https://www.youtube.com/watch?v=5PSNL1qE6VY", "https://www.youtube.com/watch?v=IThXCpk3Oc4", "https://www.youtube.com/watch?v=4lj185DaZ_o", \
			"https://www.youtube.com/watch?v=R-cdIvgBCWY", "https://www.youtube.com/watch?v=zAGVQLHvwOY", "https://www.youtube.com/watch?v=uxFJvlWqphM" };

		for (int i = 0; i < 10; i++) {
			Movie m(titles[i], genres[i], years[i], likes[i], trailers[i]);
			movies[i] = m;
		}

		return movies;
	}

	void show_movies() {
		//Zeigt alle Filme, die in der Liste sind
		if (length != 0) {
			cout << endl << "Here are all the movies that we have:" << endl;
			for (int i = 0; i < length; i++) {
				cout << "Title: " << movies[i].getTitle() << ", Genre: " << movies[i].getGenre() << \
					", Year: " << movies[i].getYear() << ", Likes: " << movies[i].getLikes() << endl;
			}
		}
		else {
			cout << endl << "There are no movies in your watchlist! Sign in as administrator and add more.";
		}
	}

	// eine Funktion um die Filme auch als Benutzer und als Admin hinzufugen
	// option = user/admin
	Movie* add_movie(Movie m, string option) {
		bool found = false;
		for (int i = 0; i < length; i++) {
			// uberprufen ob der Film in der Datenbank existiert (wir uberprufen auch das Jahr, weil einen Film in verschiedenen Jahren veroffentlich werden kann)
			if (movies[i].getTitle() == m.getTitle() && movies[i].getYear() == m.getYear()) {
				found = true;
			}
		}
		// wenn der Film nicht existiert und wir als Admin arbeiten => den Film in der Datenbank hinzufugen
		if (!found && option == "admin") {
			movies[length] = m;
			length++;
			cout << "YAY! You just added " << m.getTitle() << " in the list!" << endl;
			return movies;
		}
		// wenn der Film nicht existiert und wir als Benutzer arbeiten => kann der Film nicht in der Watchliste hinzugefugt werden 
		else if (!found && option == "user") {
			cout << "Sorry, the movie doesn't exist :(" << endl;
			return watchlist;
		}
		// wenn der Film existiert und wir als Admin arbeiten => kann der Film nicht in der Datenbank noch einmal hinzugefugt werden 
		else if (found && option == "admin") {
			cout << "Sorry, the movie already exists..." << endl;
			return movies;
		}
		// wenn der Film existiert und wir als Benutzer arbeiten => suchen wir den Film in der Watchliste 
		else if (found && option == "user") {
			bool wfound = false;
			for (int j = 0; j < wlen; j++) {
				if (watchlist[j].getTitle() == m.getTitle() && watchlist[j].getYear() == m.getYear()) {
					wfound = true;
				}
			}
			// wenn wir den Film nicht gefunden haben => wird es hinzugefugt
			if (!wfound) {
				watchlist[wlen] = m;
				wlen++;
				cout << endl << "YAY! You just added " << m.getTitle() << " in your watchlist!" << endl;
			}
			// wenn wird den Film gefunden haben => Nachricht
			else {
				cout << "Oww... it seems like you really like this movie, because you wanted to add it again in your watchlist!" << endl;
			}
			return watchlist;
		}

	}


	Movie* delete_movie_list(string title, int year) {
		//Loscht durch den Administratormode ein Film aus der Liste
		int found = -1;
		//Sucht den Film und speichert die Position
		for (int i = 0; i < length; i++) {
			if (movies[i].getTitle() == title && movies[i].getYear() == year) {
				found = i;
				break;
			}
		}
		//Verschiebt im Vektor und so wird der Film mit dem gegebenen Titel und Jahr geloscht
		if (found != -1) {
			for (int j = found + 1; j < length; j++) {
				movies[j - 1] = movies[j];
			}
			length--;
			cout << "You just deleted the movie: " << title << " from the list! Hope you are happy..." << endl;
		}
		else {
			cout << "The movie you wanted to delete was not in the list...Try to delete another movie, if you want to." << endl;
		}
		return movies;
	}

	Movie* delete_movie_watchlist(string title, int year) {
		//Loscht ein Film aus der Watchiste des Users
		int found = -1;
		if (wlen == 0) {
			cout << "Your watchlist is empty. Try adding a movie first.";
		}
		else {
			for (int i = 0; i < wlen; i++) {
				if (watchlist[i].getTitle() == title && watchlist[i].getYear() == year) {
					found = i;
					break;
				}
			}
			//Verschiebt im Vektor und so wird der Film mit dem gegebenen Titel und Jahr geloscht
			if (found == -1) {
				cout << "The movie you wanted to delete was not in the list...Try to delete another movie, if you want to." << endl;
			}
			else {
				for (int j = found + 1; j < wlen; j++) {
					watchlist[j - 1] = watchlist[j];
				}
				wlen--;
				found = true;
				cout << "You just deleted the movie: " << title << " from the list! If you liked it, you can support them with a Like . If you didn't, sorry." << endl;
				cout << "Like/Not: ";
				string option;
				cin >> option;
				if (option == "Like") {
					for (int i = 0; i < length; i++) {
						if (movies[i].getTitle() == title && movies[i].getYear() == year) {
							movies[i].setLikes(movies[i].getLikes() + 1);
							cout << "\nThank you for your support!" << endl;
							break;
						}
					}
				}
			}
		}
		return watchlist;
	}

	// option = title/genre/year/likes/trailer
	void edit_movie(string title, int year, string option) {
		bool found = false;
		if (option == "title") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir den Titel mit new_title
			for (int i = 0; i < length; i++) {
				if (movies[i].getTitle() == title && movies[i].getYear() == year) {
					cout << "New title: ";
					string new_title;
					cin.get();
					getline(cin, new_title, '\n');
					movies[i].setTitle(new_title);
					cout << "Great! You just updated the title!" << endl;
					found = true;
				}
			}
		}

		else if (option == "genre") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir das Genre mit new_genre
			for (int i = 0; i < length; i++) {
				if (movies[i].getTitle() == title && movies[i].getYear() == year) {
					cout << "New genre: ";
					string new_genre;
					cin >> new_genre;
					movies[i].setGenre(new_genre);
					cout << "Great! You just updated the genre!" << endl;
					found = true;
				}
			}
		}

		else if (option == "year") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir das Jahr mit new_year
			for (int i = 0; i < length; i++) {
				if (movies[i].getTitle() == title && movies[i].getYear() == year) {
					cout << "New year: ";
					int new_year;
					cin >> new_year;
					while (cin.fail() || new_year < 1800 || new_year>2020) {
						cout << "Please enter a valid year" << endl;
						cin.clear();
						cin.ignore(256, '\n');
						cout << "Year: ";
						cin >> new_year;
					}
					movies[i].setYear(new_year);
					cout << "Great! You just updated the year!" << endl;
					found = true;
				}
			}
		}

		else if (option == "likes") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir die Anzahl von Likes mit new_likes
			for (int i = 0; i < length; i++) {
				if (movies[i].getTitle() == title && movies[i].getYear() == year) {
					cout << "New number of likes: ";
					int new_like;
					cin >> new_like;
					movies[i].setLikes(new_like);
					cout << "Great! You just updated the likes!" << endl;
					found = true;
				}
			}
		}

		else if (option == "trailer") {
			// der Film in der Datenbank suchen; wenn wir es gefunden haben => andern wir den Trailer mit new_trailer
			for (int i = 0; i < length; i++) {
				if (movies[i].getTitle() == title && movies[i].getYear() == year) {
					cout << "New url for trailer: ";
					CString new_trailer;
					// wir lesen den URL als Char
					char myString[256];
					cin >> myString;
					// wir verwandeln dem Char in CString
					new_trailer = CString(myString);
					movies[i].setTrailer(new_trailer);
					cout << "Great! You just updated the url!" << endl;
					found = true;
				}
			}
		}

		// wenn die Option nicht gultig ist => Nachricht
		else {
			cout << "Sorry, the option is not valid..." << endl;
		}

		if (!found) {
			cout << "The movie is not in the list. Try to edit another movie.";
		}
	}

};