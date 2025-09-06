#include "movie_storage.h"
#include "movies.h"

void func(MovieStorage& storage, Movie film, char command);
void menu();

int main() {
    MovieStorage storage("movie_db", "kandik", "kandik", "127.0.0.1", "5432");
    Movie film;
    char command;

    while (true) {
        menu();
        command = getchar();

        if (command == '7') {
            break;
        }
        
        func(storage, film, command);

        std::cin.ignore(); // Очистка буфера
    }

    return 0;
}

void func(MovieStorage &storage, Movie film, char command) {
    std::string new_name;
    switch (command) {
        case '1':
            // Выбор коллекции или создание новой
            std::cin >> new_name;
            storage.new_databases(new_name);
            break;

        case '2': // ADD
            std::cout << "Enter name, genre, date (YYYY-MM-DD), rating: ";
            std::cin >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.addMovie(film.name, film.genre, film.watch_date, film.rating);
            break;
        
        case '3': // GET
            std::cout << "Enter ID: ";
            std::cin >> film.id;
            storage.getMovie(film.id);
            break;

        case '4':
            std::cout << "Enter ID, name, genre, date (YYYY-MM-DD), rating: ";
            std::cin >> film.id >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.updateMovie(film.id, film.name, film.genre, film.watch_date, film.rating);
            break;

        case '5':
            std::cout << "Enter ID: ";
            std::cin >> film.id;
            storage.deleteMovie(film.id);
            break;

        case '6':
            // показать все фильмы
            break;

        default:
            break;
    }
}

void menu() {
    std::cout << "\n1. Выбор коллекции или создание новой\n"
    "2. Добавить фильм\n"
    "3. Найти фильм по id\n"
    "4. Редактировать данные фильма\n"
    "5. Удалить фильм\n"
    "6. Показать все фильмы\n" 
    "7. Выйти\n"
    "\n"
    "Выберите действие: ";
}