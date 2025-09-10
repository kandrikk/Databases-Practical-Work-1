#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Movie.h"
//#include <nlohmann/json.hpp>

//using json = nlohmann::json;

bool isFileNameValid(std::string& file_name);
void redMessage(std::string message);
void greenMessage(std::string message);
bool fileExist(std::string& file_name);
bool createFile(std::string& file_name);

class MovieStorage {
private:
    std::string _storage;
    std::map<int, Movie> movies;

    bool connect(std::string& file_name);
    void loadMovies();
    void executeCommand(char command);
    void menu();
    bool idfree(int i);
    
public:
    MovieStorage(std::string storage);

    void interface();
    void storageSwitching(std::string& new_storage);
    void addMovie();
    void getMovie();
    void getMovie(int i);
    void updateMovie();
    void deleteMovie();
    void getAllMovies();

    void save();
};