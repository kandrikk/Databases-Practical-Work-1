#include "movie_storage.h"
#include "movies.h"

void interface(MovieStorage& storage, Movie film, char command);
void menu();

int main() {
    MovieStorage storage("movies", "movie_db", "kandik", "kandik", "127.0.0.1", "5432");
    Movie film;
    char command;

    while (true) {
        menu();
        command = getchar();

        if (command == '7') {
            break;
        }
        
        interface(storage, film, command);

        while (getchar() != '\n');
    }

    return 0;
}

void interface(MovieStorage &storage, Movie film, char command) {
    std::string new_table_name;
    switch (command) {
        case '1': //yes
            // Выбор коллекции или создание новой
            std::cout << "Введите имя хранилища: ";
            std::cin >> new_table_name;
            storage.new_collection(new_table_name);
            break;

        case '2': // yes
            std::cout << "Формат ввода: \"Название фильма\" \"Жанр\" \"Дата просмотра\"(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите фильм для добавление в хранилище: ";
            std::cin >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.addMovie(film.name, film.genre, film.watch_date, film.rating);
            break;
        
        case '3': // yes
            std::cout << "Введите id фильма: ";
            std::cin >> film.id;
            storage.getMovie(film.id);
            break;

        case '4': //yes
            std::cout << "Формат ввода: \"Название фильма\" \"Жанр\" \"Дата просмотра\"(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите данные для обновления данных в хранилище: ";
            std::cin >> film.id >> film.name >> film.genre >> film.watch_date >> film.rating;
            storage.updateMovie(film.id, film.name, film.genre, film.watch_date, film.rating);
            break;

        case '5': //yes
            std::cout << "Enter ID: ";
            std::cin >> film.id;
            storage.deleteMovie(film.id);
            break;

        case '6': // yes
            // показать все фильмы
            storage.getAllMovies();
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