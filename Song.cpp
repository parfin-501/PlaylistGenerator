#include "Song.h"

using namespace std;
// Constructor implementation
Song::Song(string t, string a, string g)
        : title(move(t)), artist(move(a)), genre(move(g)) {}

// Getter for title
string Song::getTitle() const {
    return title;
}

// Getter for artist
string Song::getArtist() const {
    return artist;
}

// Getter for genre
string Song::getGenre() const {
    return genre;
}

// Method to display song details
void Song::display() const {
    cout << "Title: " << title << ", Artist: " << artist << ", Genre: " << genre << endl;
}
