# Playlist Generator

A command-line playlist generator written in C++ that creates personalised playlists from a CSV song database based on user-selected genres.

## Features

- User signup and login
- Stores users and their preferred genres in a local CSV file
- Generates randomised playlists from three selected genres
- Limits generated playlists to a maximum of 30 matching songs
- Saves playlists for individual users
- Add new songs to the song database
- Search for songs by title
- Display the full song database
- Object-oriented design using `Song`, `Playlist`, and `User` classes

## Project Structure

```text
PlaylistGenerator/
├── main.cpp
├── Song.cpp
├── Song.h
├── Playlist.cpp
├── Playlist.h
├── User.cpp
├── User.h
├── Utils.h
├── Song_Database.csv
├── User_Database.csv
├── CMakeLists.txt
└── README.md
```

## Building

The project uses C++17 and can be built with CMake:

```bash
cmake -S . -B build
cmake --build build
```

Run the executable from the project root so that the CSV database files can be found.

## How It Works

Songs are loaded from `Song_Database.csv`. When creating a playlist, the user chooses three genres. Matching songs are filtered from the database, shuffled using the C++ standard library, and up to 30 songs are added to the generated playlist.

Saved playlists are written to a separate CSV file associated with each username.

## Notes

The login system is a demonstration feature for this university project. Passwords are transformed with a simple Caesar-style shift before being stored; this is **not secure password storage** and should not be used in a production authentication system.

## Technologies

- C++17
- CMake
- C++ Standard Library (`vector`, `algorithm`, `random`, file streams)
- CSV-based local persistence

## Author

**Naomi Parfitt**  
BSc Computer Systems Engineering  
Royal Holloway, University of London
