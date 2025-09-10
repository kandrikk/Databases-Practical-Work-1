#include "Movie.h"

bool Movie::load() {
    try {
        std::string i;
        std::cout << "ID: ";
        std::getline(std::cin, i);
        this->id = std::stoi(i);
        std::cout << "Название: ";
        std::getline(std::cin, this->name);
        std::cout << "Жанр: ";
        std::getline(std::cin, this->genre);
        std::cout << "Дата просмотра: ";
        std::getline(std::cin, this->watch_date);

        std::string rstr;
        std::cout << "Оценка фильма: ";
        std::getline(std::cin, rstr);
        this->rating = std::stoi(rstr);

        checkValid();
    } catch(std::exception) {
        std::cout << "\033[31;1m";
        std::cout << "\nНекоректнный ввод\n";
        std::cout << "\033[0m";
        return false;
    }

    return true;
}

bool Movie::load(int si) {
    while (std::getchar() != '\n');

    try {
        std::string i;

        this->id = si;
        
        std::cout << "Название: ";
        std::getline(std::cin, this->name);
        std::cout << "Жанр: ";
        std::getline(std::cin, this->genre);
        std::cout << "Дата просмотра: ";
        std::getline(std::cin, this->watch_date);

        std::cout << "Оценка фильма: ";
        std::getline(std::cin, i);
        this->rating = std::stoi(i);

        checkValid();
    } catch(std::exception) {
        std::cout << "\033[31;1m";
        std::cout << "\nНекоректнный ввод\n";
        std::cout << "\033[0m";
        return false;
    }

    return true;
}

bool Movie::checkValid() {
    if (this->id <= 0) return false;

    if (this->name.empty()) return false;
    if (this->genre.empty()) return false;

    if (this->watch_date[4] != '-' || this->watch_date[7] != '-') return false;

    int year = std::stoi(this->watch_date.substr(0));
    int mounth = std::stoi(this->watch_date.substr(5));
    int day = std::stoi(this->watch_date.substr(8));

    if (year < 1900 || year > 2025) return false;
    if (mounth < 1 || mounth > 12) return false;
    if (day < 1 || day > 31) return false;

    if (mounth == 2 && day > 28) return false;   
    if (mounth == 4 && day > 30) return false;
    if (mounth == 6 && day > 30) return false;
    if (mounth == 9 && day > 30) return false;
    if (mounth == 11 && day > 30) return false;

    return true;
};


bool Movie::parseFromString(std::string& line) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string part;

    while (std::getline(ss, part, ';')) {
        parts.push_back(part);
    }
    
    if (parts.size() != 5) {
        return false;
    }
    
    try {
        id = std::stoi(parts[0]);
        name = parts[1];
        genre = parts[2];
        watch_date = parts[3];
        rating = std::stoi(parts[4]);
    } catch (std::exception) {
        return false;
    }
    
    return true;
}