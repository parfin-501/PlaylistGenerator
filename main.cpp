#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <sstream>
#include "Song.h"
#include "Playlist.h"
#include "User.h"
#include "Utils.h"
#include <cassert>
#include <limits>

using namespace std;

// putting these into functions so I can collapse them

void menuASCIIArt()
{
    cout << "\n   __  ___              _                          \n"
            "  /  |/  / __ __  ___  (_) ____                    \n"
            " / /|_/ / / // / (_-< / / / __/                    \n"
            "/_/  /_/  \\_,_/ /___//_/  \\__/                     \n"
            "                                                   \n"
            "   ___    __                __   _        __       \n"
            "  / _ \\  / / ___ _  __ __  / /  (_)  ___ / /_      \n"
            " / ___/ / / / _ `/ / // / / /  / /  (_-</ __/      \n"
            "/_/    /_/  \\_,_/  \\_, / /_/  /_/  /___/\\__/       \n"
            "                  /___/                            \n"
            "  _____                              __            \n"
            " / ___/ ___   ___  ___   ____ ___ _ / /_ ___   ____\n"
            "/ (_ / / -_) / _ \\/ -_) / __// _ `// __// _ \\ / __/\n"
            "\\___/  \\__/ /_//_/\\__/ /_/   \\_,_/ \\__/ \\___//_/   \n"
            "                                                   " ;

}// end menuASCIIArt

void loginASCIIArt()
{
    cout << "   __                _       \n"
            "  / /  ___   ___ _  (_)  ___ \n"
            " / /__/ _ \\ / _ `/ / /  / _ \\\n"
            "/____/\\___/ \\_, / /_/  /_//_/\n"
            "           /___/             " ;
}// end loginASCIIArt

void signupASCIIArt()
{
    cout << "   ____   _                     __  __       \n"
            "  / __/  (_)  ___ _  ___       / / / /   ___ \n"
            " _\\ \\   / /  / _ `/ / _ \\     / /_/ /   / _ \\\n"
            "/___/  /_/   \\_, / /_//_/     \\____/   / .__/\n"
            "            /___/                     /_/    " ;

}// end signupASCIIArt

void addSongToDatabase() {
    string title, artist, genre;

    // Prompt the user for song details
    cout << "Enter the title of the song: ";
    getline(cin >> ws, title);  // Use ws to handle trailing newline
    cout << "Enter the artist of the song: ";
    getline(cin, artist);
    cout << "Enter the genre of the song: ";
    getline(cin, genre);

    // Open the database file in read mode to check for duplicates
    ifstream databaseFile("Song_Database.csv");
    if (!databaseFile.is_open()) {
        cerr << "Error: Unable to open the database file for reading." << endl;
        return;
    }

    string line;
    bool duplicateFound = false;

    // Check if the song already exists in the database
    while (getline(databaseFile, line)) {
        stringstream ss(line);
        string existingTitle, existingArtist, existingGenre;

        getline(ss, existingTitle, ',');
        getline(ss, existingArtist, ',');
        getline(ss, existingGenre, ',');

        // Compare title and artist (case-insensitive)
        if (toLowerCase(title) == toLowerCase(existingTitle) && toLowerCase(artist) == toLowerCase(existingArtist)) {
            duplicateFound = true;
            break;
        }
    }

    databaseFile.close();

    if (duplicateFound) {
        cout << "This song already exists in the database." << endl;
        return;
    }

    // Open the database file in append mode to add the song
    ofstream databaseFileOut("Song_Database.csv", ios::app);
    if (!databaseFileOut.is_open()) {
        cerr << "Error: Unable to open the database file for writing." << endl;
        return;
    }

    // Write the song details to the file in CSV format
    databaseFileOut << title << "," << artist << "," << genre << endl;

    // Close the file
    databaseFileOut.close();

    cout << "Song added successfully to the database!" << endl;
}

void displaySongDatabaseContents() {
    ifstream databaseFile("Song_Database.csv");

    // Check if the file opened successfully
    if (!databaseFile.is_open()) {
        cerr << "Error: Unable to open the database file." << endl;
        return;
    }

    cout << "Contents of the Song Database:" << endl;
    cout << "--------------------------------" << endl;

    string line;
    bool isEmpty = true;

    // Read and display each line
    while (getline(databaseFile, line)) {
        cout << line << endl;
        isEmpty = false;
    }

    if (isEmpty) {
        cout << "The database is empty." << endl;
    }

    // Close the file
    databaseFile.close();
}

void searchSongInDatabase() {
    ifstream databaseFile("Song_Database.csv");

    // Check if the file opened successfully
    if (!databaseFile.is_open()) {
        cerr << "Error: Unable to open the database file." << endl;
        return;
    }

    string searchTitle;
    cout << "Enter the title of the song to search for: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, searchTitle);

    string line;
    bool found = false;

    cout << "Searching for \"" << searchTitle << "\" in the database..." << endl;

    // Read each line and check if the song title matches
    while (getline(databaseFile, line)) {
        stringstream ss(line);
        string title, artist, genre;

        // Parse the line into components
        getline(ss, title, ',');
        getline(ss, artist, ',');
        getline(ss, genre, ',');

        // Check if the title matches
        if (title == searchTitle) {
            found = true;
            cout << "Found: " << title << " by " << artist << " (" << genre << ")" << endl;
        }
    }

    if (!found) {
        cout << "No song found with the title \"" << searchTitle << "\"." << endl;
    }

    // Close the file
    databaseFile.close();
}


void generatePlaylist(User& username) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string playlistName;
    cout << "Enter the name of your playlist: ";
    getline(cin, playlistName);

    Playlist myPlaylist(playlistName);

    vector<string> selectedGenres;
    string genre;

    cout << "Enter 3 genres for your playlist: " << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "Genre " << (i + 1) << ": ";
        cin >> genre;
        selectedGenres.push_back(toLowerCase(genre)); // Convert to lowercase
    }

    myPlaylist.generatePlaylist(selectedGenres);
    myPlaylist.display();

    cout << "Would you like to save this playlist? (y/n): ";
    char saveChoice;
    cin >> saveChoice;

    if (saveChoice == 'y' || saveChoice == 'Y') {
        myPlaylist.saveToDatabase(username.getPlaylistFileName());
    } else {
        cout << "Playlist not saved." << endl;
    }
}

void displayAllPlaylists(User& username) {
    ifstream playlistFile(username.getPlaylistFileName());

    if (!playlistFile.is_open()) {
        cerr << "Error: Unable to open the playlist database for " << username.szUserName << "." << endl;
        return;
    }

    cout << "All Playlists for " << username.szUserName << ":\n";
    cout << "------------------------------------------\n";

    string line;
    bool isPlaylistHeader = false;

    while (getline(playlistFile, line)) {
        if (line.empty()) {
            cout << endl;
            isPlaylistHeader = false;
        } else if (line.rfind("Playlist:", 0) == 0) {
            cout << line << endl;
            cout << "-----------------------------" << endl;
            isPlaylistHeader = true;
        } else if (isPlaylistHeader) {
            cout << line << endl;
        }
    }

    playlistFile.close();
}

void enterPlaylistMenu(User& username) {
    menuASCIIArt();

    string userInput;
    do {
        cout << "\n\nWelcome " << username.szUserName << "\n\nPlease pick from the following options:\n\n";
        cout << "1) View Your Saved Playlists\n";
        cout << "2) Make a New Playlist\n";
        cout << "3) Add a Song to Database\n";
        cout << "4) Search for a Song\n";
        cout << "5) Display All Songs\n";
        cout << "6) Quit\n\n";
        cin >> userInput;

        try {
            int choice = stoi(userInput);

            if (choice < 1 || choice > 6) {
                cout << "Invalid input. Please enter a number between 1 and 6.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    displayAllPlaylists(username);
                    break;
                case 2:
                    generatePlaylist(username);
                    break;
                case 3:
                    addSongToDatabase();
                    break;
                case 4:
                    searchSongInDatabase();
                    break;
                case 5:
                    displaySongDatabaseContents();
                    break;
                case 6:
                    cout << "Exiting program. Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid input. Please try again.\n";
            }

            // Wait for the user to press Enter before returning to the menu
            cout << "\nPress Enter to return to the main menu...";
            cin.ignore(); // Clear input buffer
            cin.get();    // Wait for Enter key
        } catch (const exception&) {
            cout << "Invalid input. Please enter a valid number between 1 and 6.\n";
        }
    } while (true);
}

void doUserLogin()
{
    loginASCIIArt();

    string szUsername ;
    string szPassword ;

    cout << "\n\nPlease enter your username:" ;
    cin >> szUsername;
    cout << "\nPlease enter your password:" ;
    cin >> szPassword ;

    ifstream databaseFile("User_Database.csv");

    // Check if the file opened successfully
    if (!databaseFile.is_open()) {
        cerr << "Error: Unable to open the database file." << endl;
        return;
    }

    string line;
    bool found = false;

    cout << "Searching for \"" << szUsername << "\" in the database..." << endl;

    // encrypt password
    const int iShift = 3;
    for (char& character : szPassword) {
        character = static_cast<char>(character + iShift);
    }// end for

    // Read each line and check if the user and password matches
    while (getline(databaseFile, line)) {
        stringstream ss(line);
        string user, pass;
        string szfavGenres [3] ;

        // Parse the line into components
        getline(ss, user, ',');
        getline(ss, pass, ',');
        getline(ss, szfavGenres[0], ',');
        getline(ss, szfavGenres[1], ',');
        getline(ss, szfavGenres[2], ',');

        // Check if the info matches
        if (user == szUsername && pass == szPassword) {
            found = true;
            cout << "User Found!" << endl;


            User currentUser = {szUsername, szPassword, {szfavGenres[0], szfavGenres[1], szfavGenres[2]} };
            enterPlaylistMenu(currentUser) ;
        }
    }

    if (!found) {
        cout << "\nUsername/Password is incorrect, ending program... " << endl;
    }

    // Close the file
    databaseFile.close();

}// end doUserLogin

void doUserSignUp() {
    signupASCIIArt();

    string szUserName;
    string szPassword;
    string szfavGenres[3];

    // List of genres in lowercase for comparison
    string szGenres[] = {"country", "jazz", "rock", "hip-hop", "edm",
                         "latin", "classical", "pop", "metal", "indie",
                         "folk", "punk", "rnb", "reggae", "alternative"};


    cout << "\n\nPlease create a new username:  ";
    cin >> szUserName;
    cout << "\nPlease create a new password:  ";
    cin >> szPassword;
    cout << "\nHere's a list of genres, pick your top 3:\n";

    cout << "\nCountry, Jazz, Rock, Hip-hop, EDM\n"
            "Latin, Classical, Pop, Metal, Indie\n"
            "Folk, Punk, Rnb, Reggae, Alternative\n";

    for (int i = 0; i < 3;) {
        cout << "\nPick your preferred genre " << (i + 1) << ": ";
        cin >> szfavGenres[i];

        // Convert user input to lowercase
        string userGenre = toLowerCase(szfavGenres[i]); // Using the toLowerCase utility function

        // Check if the entered genre is valid
        bool isValid = false;
        for (const string& genre : szGenres) {
            if (userGenre == genre) {
                szfavGenres[i] = genre; // Store the validated genre
                isValid = true;
                i++; // Move to the next genre
                break;
            }
        }

        if (!isValid) {
            cout << "Invalid genre. Please pick a genre from the list.\n";
        }
    }

    // Encrypt password
    const int iShift = 3;
    for (char& character : szPassword) {
        character = static_cast<char>(character + iShift);
    }

    User currentUser = {szUserName, szPassword, {szfavGenres[0], szfavGenres[1], szfavGenres[2]}};

    ofstream userFile("User_Database.csv", ios::app);
    if (!userFile.is_open()) {
        cerr << "Error: Unable to open the user database." << endl;
        return;
    }

    userFile << currentUser.szUserName << ","
             << currentUser.szPassword << ","
             << currentUser.szfavGenres[0] << ","
             << currentUser.szfavGenres[1] << ","
             << currentUser.szfavGenres[2] << "\n";
    userFile.close();

    enterPlaylistMenu(currentUser);
}

void enterMainMenu()
{
    menuASCIIArt();

    string szUserInput;

    cout << "\n\nWelcome to our music playlist generator!\n\n";

    while (true) {
        cout << "Please pick from the following options:\n\n";
        cout << "1) Login (Returning User)\n2) Sign Up (New User)\n3) Quit\n\n";
        cin >> szUserInput;

        if (szUserInput == "1") {
            doUserLogin();
            return;
        } else if (szUserInput == "2") {
            doUserSignUp();
            return;
        } else if (szUserInput == "3") {
            cout << "Goodbye!" << endl;
            return;
        }

        cout << "Invalid input. Please enter 1, 2, or 3.\n";
    }

}// end enterMainMenu

void testUserClass() {
    // Test User constructor
    User user("testUser", "testPass", {"rock", "pop", "jazz"});
    assert(user.szUserName == "testUser");
    assert(user.szPassword == "testPass");
    assert(user.szfavGenres[0] == "rock");
    assert(user.szfavGenres[1] == "pop");
    assert(user.szfavGenres[2] == "jazz");

    // Test getPlaylistFileName
    assert(user.getPlaylistFileName() == "testUser_Playlist_Database.csv");
    cout << "User class tests passed!\n";
}

void testToLowerCase() {
    // Test toLowerCase
    assert(toLowerCase("HELLO") == "hello");
    assert(toLowerCase("MixedCase123") == "mixedcase123");
    assert(toLowerCase("alreadylower") == "alreadylower");
    cout << "toLowerCase tests passed!\n";
}

int main()
{
    enterMainMenu();
    //testUserClass();
    //testToLowerCase();

}// end main
