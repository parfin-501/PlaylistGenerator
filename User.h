#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
public:
    // Member variables
    string szUserName;  // Username
    string szPassword;  // Password
    vector<string> szfavGenres;  // Favorite genres

public:
    // Constructor
    User(string n, string p, vector<string> szfavGenres);

    // Method to get the filename for user's playlist database
    string getPlaylistFileName() const;
};

#endif // USER_H