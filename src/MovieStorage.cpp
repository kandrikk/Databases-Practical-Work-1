#include "MovieStorage.h"

MovieStorage::MovieStorage() {
    connect(_storage);
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

void MovieStorage::storageSwitching(std::string& new_storage) {
    connect(new_storage);
}

void MovieStorage::addMovie() {
    std::string line;
    std::getline(std::cin, line);

    //Movie mov = linkMovie(line);
}

// hellpers

void MovieStorage::menu() {
    std::string message = "\nПодключенно к хранилищу " + _storage.substr(5) + ".";
    greenMessage(message);

    std::cout << "\n1. Выбор или создание нового хранилищаа\n"
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
    std::string new_storage;
    Movie film;

    switch (command) {
        case '1':
            std::cout << "Введите имя таблицы: ";
            std::cin >> new_storage;
            this->storageSwitching(new_storage);
            break;

        case '2':
            std::cout << "Формат ввода: ID \"Название фильма\" \"Жанр\" \"Дата просмотра\"(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите фильм для добавление в хранилище: ";
            this->addMovie();
            break;
        
        case '3':
            std::cout << "Введите id фильма: ";
            
            //this->getMovie(film.id);
            break;

        case '4':
            std::cout << "Формат ввода: ID \"Название фильма\" Жанр Дата_просмотра(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите данные для обновления данных в хранилище: ";

            //this->updateMovie(film.id, film.name, film.genre, film.watch_date, film.rating);
            break;

        case '5':
            std::cout << "Введите ID для удаления: ";

            //this->deleteMovie(film.id);
            break;

        case '6':
            //this->getAllMovies();
            break;

        default:
            break;
    }
}

void MovieStorage::connect(std::string& file_name) {
    if (!isFileNameValid(file_name)) {
        std::string message = "\n" + file_name + " не соответствует формату \"namefile.txt\".\n";
        redMessage(message);
        return;
    }

    file_name = "data/" + file_name;

    if (!fileExist(file_name)) {
        createFile(file_name);
    }

    std::fstream file(file_name);

    if (file.is_open()) {
        _storage = file_name;
    } else {
        std::string message = "\nНеудалось открыть хранилище " + file_name.substr(5) + ".\n";
        redMessage(message);
    }
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

void redMessage(std::string& message) {
    std::cout << "\033[31;1m";
    std::cout << message;
    std::cout << "\033[0m";
}

void greenMessage(std::string& message) {
    std::cout << "\u001b[32;1m";
    std::cout << message;
    std::cout << "\033[0m";
}

