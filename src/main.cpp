#include "movie_storage.h"
#include "movies.h"

void interface(MovieStorage& storage, Movie &film, char command);

int main() {
    MovieStorage storage("movies", "movie_db", "kandik", "kandik", "127.0.0.1", "5432");
    Movie film;
    char command;

    while (true) {
        storage.menu();
        std::cin >> command;

        if (command == '7') {
            break;
        }
        
        if (command >= '1' && command <= '6') {
            interface(storage, film, command);
        } else {
            std::cout << "\033[31;1m";
            std::cout << "\nНеверный ввод команды.\n";
            std::cout << "\033[0m";
        }
    }

    return 0;
}

void interface(MovieStorage &storage, Movie &film, char command) {
    std::string new_table_name;

    switch (command) {
        case '1':
            std::cout << "Введите имя таблицы: ";
            std::cin >> new_table_name;
            storage.tableSwitching(new_table_name);
            break;

        case '2':
            std::cout << "Формат ввода: \"Название фильма\" \"Жанр\" \"Дата просмотра\"(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите фильм для добавление в хранилище: ";
            std::cin >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.addMovie(film.name, film.genre, film.watch_date, film.rating);
            break;
        
        case '3':
            std::cout << "Введите id фильма: ";
            std::cin >> film.id;
            storage.getMovie(film.id);
            break;

        case '4':
            std::cout << "Формат ввода: ID \"Название фильма\" Жанр Дата_просмотра(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите данные для обновления данных в хранилище: ";
            std::cin >> film.id >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.updateMovie(film.id, film.name, film.genre, film.watch_date, film.rating);
            break;

        case '5':
            std::cout << "Введите ID для удаления: ";
            std::cin >> film.id;
            storage.deleteMovie(film.id);
            break;

        case '6':
            storage.getAllMovies();
            break;

        default:
            break;
    }
}