#include "MovieStorage.h"

MovieStorage::MovieStorage(std::string storage) {
    if (connect(storage)) {
        this->loadMovies();
    }
}

void MovieStorage::interface() {
    std::string line;
    char command;

    while (true) {
        this->menu();
        std::getline(std::cin, line);

        if (line.length() == 1 && line[0] >= '1' && line[0] <= '7') {
            command = line[0];
            
            if (command == '7') {
                break;
            }
        
            this->executeCommand(command);
        } else {
            std::string message = "\nНеверный ввод команды.\n";
            redMessage(message);
        }
    }
}

void MovieStorage::storageSwitching() {
    std::string new_storage;

    std::cout << "Введите имя хранилища: ";
    std::getline(std::cin, new_storage);

    if (connect(new_storage)) {
        this->loadMovies();
    }
}

void MovieStorage::addMovie() {
    Movie mov;
    if (!mov.load()) {
        redMessage("\nНеверный формат ввода.\n");
        return;
    }

    if (!idfree(mov.id)) {
        redMessage("\nID занято.\n");
        return;
    }

    movies.insert(std::make_pair(mov.id, mov));

    save();
}

void MovieStorage::getMovie() {
    int i;
    std::string stri;
    std::cout << "ID: ";
    std::getline(std::cin, stri);

    if (stri.length() == 1) {
        i = std::stoi(stri);
    } else {
        redMessage("\nНеккоректнный ввод.\n");
        return;
    }

    if (idfree(i)) {
        redMessage("\nФильма с данным ID нет в базе.\n");
        return;
    }

    std::string mov = "\nНазвание: " + movies[i].name + "\n"
                    + "Жанр: " + movies[i].genre + "\n"
                    + "Дата просмотра: " + movies[i].watch_date + "\n"
                    + "Оценка: " + std::to_string(movies[i].rating) + "\n";

    greenMessage(mov);
}

void MovieStorage::getMovie(int i) {
    std::string mov = "\nID: " + std::to_string(movies[i].id) + "\n" 
                    + "Название: " + movies[i].name + "\n"
                    + "Жанр: " + movies[i].genre + "\n"
                    + "Дата просмотра: " + movies[i].watch_date + "\n"
                    + "Оценка: " + std::to_string(movies[i].rating) + "\n";

    greenMessage(mov);
}

void MovieStorage::updateMovie() {
    Movie mov;

    int i;
    std::string stri;
    std::cout << "ID: ";
    std::getline(std::cin, stri);

    if (stri.length() == 1) {
        i = std::stoi(stri);
    } else {
        redMessage("\nНеккоректнный ввод.\n");
        return;
    }

    if (idfree(i)) {
        redMessage("\nФильма с данным ID нет в базе.\n");
        return;
    }

    if (!mov.load(i)) {
        redMessage("\nНеверный формат ввода.\n");
        return;
    }

    movies[i] = mov;

    save();
}

void MovieStorage::deleteMovie() {
    int i;
    std::string stri;
    std::cout << "ID: ";
    std::getline(std::cin, stri);

    if (stri.length() == 1) {
        i = std::stoi(stri);
    } else {
        redMessage("\nНеккоректнный ввод.\n");
        return;
    }
    
    if (idfree(i)) {
        redMessage("\nФильма с данным ID нет в базе.\n");
        return;
    }

    movies.erase(i);
    
    save();

    greenMessage("\nФильм удален\n");
}

void MovieStorage::getAllMovies() {
    if (movies.empty()) {
        redMessage("\nВ хранилище нет фильмов.\n");
    }

    std::vector<std::pair<int, Movie>> sortedMovies(movies.begin(), movies.end());

    for (auto pair : sortedMovies) {
        getMovie(pair.first);
    }
}

void MovieStorage::save() {
    std::string filename = _storage;
    std::ofstream file(filename);

    if (!file.is_open()) {
        redMessage("Не удалось открыть файл");
        return;
    }

    for (auto it : movies) {
        std::string line = ";" + it.second.name + ";" 
        + it.second.genre + ";" + it.second.watch_date + ";" 
        + std::to_string(it.second.rating);

        file << it.first << line << "\n";
    }
}

void MovieStorage::loadMovies() {
    movies.clear();
    
    std::ifstream file(_storage);
    if (!file.is_open()) {
        std::string message = "\nНе удалось открыть хранилище " + _storage + " для чтения.\n";
        redMessage(message);
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
        
        Movie movie;
        if (movie.parseFromString(line)) {
            movies[movie.id] = movie;
        } else {
            std::string message = "\nОшибка при чтении строки: " + line + "\n";
            redMessage(message);
        }
    }
    
    file.close();
}

// hellpers

bool MovieStorage::idfree(int i) {
    if (movies.find(i) != movies.end()) {
        return false;
    }

    return true;
}

void MovieStorage::menu() {
    std::string message = "\nПодключенно к хранилищу " + _storage.substr(5) + ".";
    greenMessage(message);

    std::cout << "\n1. Выбор или создание нового хранилища\n"
    "2. Добавить фильм\n"
    "3. Найти фильм по id\n"
    "4. Редактировать данные фильма\n"
    "5. Удалить фильм\n"
    "6. Показать все фильмы\n" 
    "7. Выйти\n"
    "\n"
    "Выберите действие: ";
}

void MovieStorage::executeCommand(char command) {
    switch (command) {
        case '1':
            this->storageSwitching();
            break;

        case '2':
            this->addMovie();
            break;
        
        case '3':            
            this->getMovie();
            break;

        case '4':
            this->updateMovie();
            break;

        case '5':
            this->deleteMovie();
            break;

        case '6':
            this->getAllMovies();
            break; 

        default:
            break;
    }
}

bool MovieStorage::connect(std::string& filename) {
    if (!isFileNameValid(filename)) {
        std::string message = "\n" + filename + " не соответствует формату \"namefile.txt\".\n";
        redMessage(message);
        return false;
    }

    filename = "data/" + filename;

    if (!fileExist(filename)) {
        std::string assert;

        std::cout << "Хранилища " << filename.substr(5) << " несуществует.\nСоздать?\n[yes/no]: ";
        std::cin.ignore();
        std::getline(std::cin, assert);

        if (assert == "yes") {
            createFile(filename);
            std::string message = "\nХранилище " + filename.substr(5) + " созданно.\n";
            greenMessage(message);
        } else if (assert == "no") {
            return false;
        } else {
            redMessage("\nНекоректнный ввод.\n");
            return false;
        }
    }

    std::fstream file(filename);

    if (!file.is_open()) {
        std::string message = "\nНеудалось открыть хранилище " + filename.substr(5) + ".\n";
        redMessage(message);
        return false;
    }

    _storage = filename;
    return true;
}

bool isFileNameValid(std::string& file_name) {
    if (file_name.length() < 5) return false;
    if (file_name.substr(file_name.length() - 4) != ".txt") return false;

    return true;
}

bool fileExist(std::string& file_name) {
    std::ifstream file(file_name);
    return file.good();
}

bool createFile(std::string& file_name) {
    std::ofstream file(file_name);

    if (!file) {
        return false;
    }

    file.close();
    return true;
}

void redMessage(std::string message) {
    std::cout << "\033[31;1m";
    std::cout << message;
    std::cout << "\033[0m";
}

void greenMessage(std::string message) {
    std::cout << "\u001b[32;1m";
    std::cout << message;
    std::cout << "\033[0m";
}