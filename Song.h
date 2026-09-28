#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>

using namespace std;

// Song class declaration
class Song {
private:
    string title;   // Title of the song
    string artist;  // Artist of the song
    string genre;   // Genre of the song

public:
    // Constructor
    Song(string t, string a, string g);

    // Getters for song attributes
    string getTitle() const;  // Get the title of the song
    string getArtist() const; // Get the artist of the song
    string getGenre() const;  // Get the genre of the song

    // Method to display song details
    void display() const;
};

#endif // SONG_H
