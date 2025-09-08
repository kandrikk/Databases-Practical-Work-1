#include "movie_storage.h"

MovieStorage::MovieStorage(const std::string& table_name, const std::string& db_name, 
    const std::string& user, const std::string& password, const std::string& host, 
    const std::string& port)
    : _table_name(table_name), _db_name(db_name), _user(user), 
    _password(password), _host(host), _port(port)
{
    connect();
}

void MovieStorage::tableSwitching(const std::string& table_name) {
    std::string agree;
    
    if (!tableExists(table_name)) {
        std::cout << "Хранилища '" << table_name << "' не существует." << std::endl;

        std::cout << "Создать новое хранилище " << table_name << "?" << std::endl;
        std::cout << "[yes/no]: ";
        std::cin >> agree;

        if (agree == "yes") {
            _table_name = table_name;
            createTable();
        }
        
    } else {
        _table_name = table_name;
    }
}

void MovieStorage::addMovie(const std::string& name, const std::string& genre, 
    const std::string& watch_date, int rating) 
{
    try {
        pqxx::work txn(*conn);
        txn.exec("INSERT INTO " + txn.quote_name(_table_name) 
            + " (name, genre, watch_date, rating) VALUES (" 
            + txn.quote(name) + ", " + txn.quote(genre) + ", " 
            + txn.quote(watch_date) + ", " + txn.quote(rating) + ")");
        txn.commit();  
    } catch (const std::exception &e){
        std::cout << "\033[31;1m";
        std::cout << "\nОшибка при добавление фильма, пожалуйста проверьте формат ввода.\n" << std::endl;
        std::cout << "\033[0m";
    }
}

void MovieStorage::getMovie(int id) {
    pqxx::work txn(*conn);
    pqxx::result res = txn.exec("SELECT * FROM  " + txn.quote_name(_table_name) 
    + "  WHERE id = " + txn.quote(id));

    if (res.empty()) {
        std::cout << "\033[31;1m";
        std::cout << "\nФильма по такому ID нет в хранилище.\n";
        std::cout << "\033[0m";
    } else {
        std::cout << "\u001b[32;1m";
        for (const auto& row : res) {
            std::cout << "\nName: " << row[1].as<std::string>()
                        << ", Genre: " << row[2].as<std::string>()
                        << ", Date: " << row[3].as<std::string>()
                        << ", Rating: " << row[4].as<std::string>()
                        << std::endl;
        std::cout << "\033[0m";
        }
    }
}

void MovieStorage::updateMovie(int id, const std::string& name, 
    const std::string& genre, const std::string& watch_date, int rating) 
{
    if (!idExists(id)) {
        std::cout << "\033[31;1m";
        std::cout << "\nФильма с данным ID нет в хранилище.\n";
        std::cout << "\033[0m";
        return;
    }

    if (name.empty()) {
        std::cout << "\033[31;1m";
        std::cout << "Ошибка: название фильма не может быть пустым.\n";
        std::cout << "\033[0m";
        return;
    }

    if (rating < 0 || rating > 10) {
        std::cout << "\033[31;1m";
        std::cout << "Ошибка: рейтинг должен быть в диапазоне от 0 до 10.\n";
        std::cout << "\033[0m";
        return;
    }

    if (!watch_date.empty() && !isValidDate(watch_date)) {
        std::cout << "\033[31;1m";
        std::cout << "Ошибка: неверный формат даты. Используйте YYYY-MM-DD.\n";
        std::cout << "\033[0m";
        return;
    }

    try {
        pqxx::work txn(*conn);
        
        std::string query = "UPDATE " + txn.quote_name(_table_name) + 
            " SET name = $1, genre = $2, watch_date = $3, rating = $4 WHERE id = $5";
        
        pqxx::params params;
        params.append(name);
        params.append(genre);
        params.append(watch_date);
        params.append(rating);
        params.append(id);
        
        txn.exec(query, params);
        txn.commit();
        
        std::cout << "\u001b[32;1m";
        std::cout << "Фильм с ID " << id << " успешно обновлен!\n";
        std::cout << "\033[0m";
        
    } catch (const std::exception& e) {
        std::cout << "\033[31;1m";
        std::cout << "Ошибка при обновлении фильма: " << e.what() << std::endl;
        std::cout << "\033[0m";
    }
}

void MovieStorage::deleteMovie(int id) {
    if (!idExists(id)) {
        std::cout << "\033[31;1m";
        std::cout << "\nФильма по такому ID нет в хранилище.\n";
        std::cout << "\033[0m";
        return;
    }

    pqxx::work txn(*conn);
    txn.exec("DELETE FROM " + txn.quote_name(_table_name) 
    + " WHERE id = " + txn.quote(id));
    txn.commit();
}

void MovieStorage::getAllMovies() {
    pqxx::work txn(*conn);
    
    std::string query = "SELECT * FROM " + txn.quote_name(_table_name) + " ORDER BY id";
    pqxx::result result = txn.exec(query);
    
    if (result.empty()) {
        std::cout << "\033[31;1m";
        std::cout << "\nВ хранилище нет фильмов" << std::endl;
        std::cout << "\033[0m";
    } else {
        std::cout << "\u001b[32;1m";
        std::cout << "Список всех фильмов:" << std::endl;
        
        for (const auto& row : result) {
            std::cout << "\nID: " << row["id"].as<int>()
                        << " Name: " << row["name"].as<std::string>()
                        << " Genre: " << row["genre"].as<std::string>()
                        << " Release Date: " << row["watch_date"].as<std::string>()
                        << " Rating: " << row["rating"].as<std::string>();
        }
        std::cout << "\033[0m" << std::endl;
    }
    
    txn.commit();
}

void MovieStorage::menu() {
    std::cout << "\u001b[32;1m";
    std::cout << "\nПодключенно к хранилищу " << _table_name << ".";
    std::cout << "\033[0m";

    std::cout << "\n1. Выбор или создание новой таблицы\n"
    "2. Добавить фильм\n"
    "3. Найти фильм по id\n"
    "4. Редактировать данные фильма\n"
    "5. Удалить фильм\n"
    "6. Показать все фильмы\n" 
    "7. Выйти\n"
    "\n"
    "Выберите действие: ";
}

void MovieStorage::interface() {
    char command;

    while (true) {
        this->menu();
        std::cin >> command;

        if (command == '7') {
            break;
        }
        
        if (command >= '1' && command <= '6') {
            this->executeCommand(command);
        } else {
            std::cout << "\033[31;1m";
            std::cout << "\nНеверный ввод команды.\n";
            std::cout << "\033[0m";
        }
    }
}

// ВСПОМОГАТЕЛЬНЫЕ

void MovieStorage::executeCommand(char command) {
    std::string new_table_name;
    Movie film;

    switch (command) {
        case '1':
            std::cout << "Введите имя таблицы: ";
            std::cin >> new_table_name;
            this->tableSwitching(new_table_name);
            break;

        case '2':
            std::cout << "Формат ввода: \"Название фильма\" \"Жанр\" \"Дата просмотра\"(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите фильм для добавление в хранилище: ";
            std::cin >> film.name >> film.genre >> film.watch_date >> film.rating;
            this->addMovie(film.name, film.genre, film.watch_date, film.rating);
            break;
        
        case '3':
            std::cout << "Введите id фильма: ";
            std::cin >> film.id;
            this->getMovie(film.id);
            break;

        case '4':
            std::cout << "Формат ввода: ID \"Название фильма\" Жанр Дата_просмотра(YYYY-MM-DD) Рейтинг(0-10)\n";
            std::cout << "Введите данные для обновления данных в хранилище: ";
            std::cin >> film.id >> film.name >> film.genre >> film.watch_date >> film.rating;
            this->updateMovie(film.id, film.name, film.genre, film.watch_date, film.rating);
            break;

        case '5':
            std::cout << "Введите ID для удаления: ";
            std::cin >> film.id;
            this->deleteMovie(film.id);
            break;

        case '6':
            this->getAllMovies();
            break;

        default:
            break;
    }
}

void MovieStorage::connect() {
    std::string conn_str = "dbname=" + _db_name + " user=" + _user
    + " password=" + _password + " hostaddr=" + _host + " port=" + _port;

    conn = std::make_unique<pqxx::connection>(conn_str);
}

bool MovieStorage::tableExists(const std::string& tableName) {
    pqxx::work txn(*conn);
    
    std::string query = R"(
        SELECT EXISTS (
            SELECT FROM information_schema.tables 
            WHERE table_schema = 'public' 
            AND table_name = $1
        )
    )";

    pqxx::params params;
    params.append(tableName);
    pqxx::result result = txn.exec(query, params);
    
    txn.commit();
    
    return result[0][0].as<bool>();
}

void MovieStorage::createTable() {
    pqxx::work txn(*conn);
    
    std::string createTableSQL = R"(
        CREATE TABLE )" + _table_name + R"( (
            id SERIAL PRIMARY KEY,
            name VARCHAR(255) NOT NULL,
            genre VARCHAR(255),
            watch_date DATE,
            rating INTEGER CHECK (rating >= 0 AND rating <= 10)
        )
    )";
    
    txn.exec(createTableSQL);
    txn.commit();
    
    std::cout << "Таблица '" << _table_name << "' успешно создана." << std::endl;
}

bool MovieStorage::idExists(int id) {
    pqxx::work txn(*conn);
    
    std::string query = "SELECT EXISTS(SELECT 1 FROM " + txn.quote_name(_table_name) + 
                        " WHERE id = $1)";
    
    pqxx::params params;
    params.append(id);
    
    pqxx::result result = txn.exec(query, params);
    txn.commit();
    
    return result[0][0].as<bool>();
}

bool MovieStorage::isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));
    
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    return true;
}