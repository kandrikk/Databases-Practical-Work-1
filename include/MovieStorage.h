#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Movie.h"

bool isFileNameValid(std::string& file_name);
void redMessage(std::string& message);
void greenMessage(std::string& message);
bool fileExist(std::string& file_name);
bool createFile(std::string& file_name);

class MovieStorage {
private:
    std::string _storage = "storage.txt";
    std::map<int, Movie> movies;

    void connect(std::string& file_name);
    void executeCommand(char command);
    void menu();
    
public:
    MovieStorage();

    void interface();
    void storageSwitching(std::string& new_storage);
    void addMovie();
};