#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Movie.h"
#include "helpers.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MovieStorage {
private:
    std::string _storage;
    std::map<int, Movie> movies;

    void menu();
    void executeCommand(char command);
    bool connect(std::string& file_name);
    void loadMovies();
    void save();
    
    bool isFileNameValid(std::string& file_name);
    bool fileExist(std::string& file_name);
    bool createFile(std::string& file_name);
    bool idfree(int i);
    
public:
    MovieStorage(std::string storage);

    void interface();
    void storageSwitching();
    void addMovie();
    void getMovie();
    void getMovie(int i);
    void updateMovie();
    void deleteMovie();
    void getAllMovies();
};