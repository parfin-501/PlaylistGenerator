#include "Playlist.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <cctype>
#include "Utils.h"

using namespace std;

// Constructor implementation
Playlist::Playlist(string playlistName) : name(move(playlistName)) {}

// Setter for playlist name
void Playlist::setName(const string& playlistName) {
    name = playlistName;
}

void Playlist::generatePlaylist(const vector<string>& selectedGenres) {
    ifstream databaseFile("Song_Database.csv");
    if (!databaseFile.is_open()) {
        cerr << "Error: Unable to open the song database." << endl;
        return;
    }

    vector<Song> songLibrary;
    string line;

    while (getline(databaseFile, line)) {
        stringstream ss(line);
        string title, artist, genre;

        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');

        songLibrary.emplace_back(title, artist, genre);
    }

    databaseFile.close();

    vector<Song> filteredSongs;
    for (const auto& song : songLibrary) {
        string songGenre = toLowerCase(song.getGenre());
        for (const auto& genre : selectedGenres) {
            if (songGenre == toLowerCase(genre)) {
                filteredSongs.push_back(song);
            }
        }
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(filteredSongs.begin(), filteredSongs.end(), gen);

    songs.clear();
    for (size_t i = 0; i < min(filteredSongs.size(), static_cast<size_t>(30)); ++i) {
        songs.push_back(filteredSongs[i]);
    }
}
// Method to display the playlist
void Playlist::display() const {
    cout << "Playlist: " << name << endl;
    cout << "-----------------------------" << endl;

    if (songs.empty()) {
        cout << "No songs match the selected genres!" << endl;
        return;
    }

    for (const auto& song : songs) {
        song.display();
    }
}

// Method to save the playlist to the database
void Playlist::saveToDatabase(const string& fileName) const {
    ofstream playlistFile(fileName, ios::app);

    if (!playlistFile.is_open()) {
        cerr << "Error: Unable to open the playlist database." << endl;
        return;
    }

    // Write the playlist name as a header
    playlistFile << "Playlist: " << name << "\n";

    // Write each song in the playlist
    for (const auto& song : songs) {
        playlistFile << song.getTitle() << "," << song.getArtist() << "," << song.getGenre() << "\n";
    }

    playlistFile << "\n"; // Separate playlists with an empty line
    playlistFile.close();

    cout << "Playlist saved to " << fileName << "!" << endl;
}
