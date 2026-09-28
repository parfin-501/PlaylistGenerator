#include "User.h"

using namespace std;

// Constructor implementation
User::User(string n, string p, vector<string> favGenres)
        : szUserName(move(n)), szPassword(move(p)), szfavGenres(move(favGenres)) {}

// Method to get the filename for the user's playlist database
string User::getPlaylistFileName() const {
    return szUserName + "_Playlist_Database.csv";
}