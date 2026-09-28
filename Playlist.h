#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <vector>
#include <string>
#include <random>

using namespace std;
class Playlist {
private:
    string name;                  // Playlist name
    vector<Song> songs;           // Vector of songs in the playlist

public:
    // Constructor
    explicit Playlist(string playlistName);

    // Setter for playlist name
    void setName(const string& playlistName);

    // Method to generate a playlist based on user-selected genres
    void generatePlaylist(const vector<string>& selectedGenres);

    // Method to display the playlist
    void display() const;

    // Method to save the playlist to a database
    void saveToDatabase(const std::string& fileName) const;

};

#endif // PLAYLIST_H
