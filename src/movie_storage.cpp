#include "movie_storage.h"

MovieStorage::MovieStorage(const std::string& table_name, const std::string& db_name, 
    const std::string& user, const std::string& password, const std::string& host, 
    const std::string& port)
    : _table_name(table_name), _db_name(db_name), _user(user), 
    _password(password), _host(host), _port(port)
{
    connect();
}

void MovieStorage::connect() {
    std::string conn_str = "dbname=" + _db_name + " user=" + _user
    + " password=" + _password + " hostaddr=" + _host + " port=" + _port;

    conn = std::make_unique<pqxx::connection>(conn_str);

    if (conn->is_open()) {
        std::cout << "\u001b[32;1m";
        std::cout << "Соединение с хранилищем успешно!" << std::endl;
        std::cout << "\033[0m";
    } else {
        std::cout << "\033[31;1m";
        std::cout << "Неудалось установить соединение." << std::endl;
        std::cout << "\033[0m";
    }
}

void MovieStorage::getAllMovies() {
    // Создаем транзакцию
    pqxx::work txn(*conn);
    
    // Выполняем запрос для получения всех фильмов
    std::string query = "SELECT * FROM " + txn.quote_name(_table_name) + " ORDER BY id";
    pqxx::result result = txn.exec(query);
    
    if (result.empty()) {
        std::cout << "В хранилище нет фильмов" << std::endl;
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

void MovieStorage::new_collection(const std::string& table_name) {
    _table_name = table_name;
    
    // Проверяем существование таблицы
    if (!tableExists(_table_name)) {
        std::cout << "Таблица '" << _table_name << "' не существует. Создаем новую таблицу..." << std::endl;
        createTable();
    } else {
        std::cout << "Подключаемся к существующей таблице '" << _table_name << "'" << std::endl;
    }
    
    // Подключаемся к базе данных
    connect();
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
    
    // Явно указываем использование параметризованного запроса
    pqxx::params params;
    params.append(tableName);
    pqxx::result result = txn.exec(query, params);
    
    txn.commit();
    
    return result[0][0].as<bool>();
}

void MovieStorage::createTable() {
    try {
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
        
    } catch (const std::exception &e) {
        std::cout << "\033[31;1m";
        std::cout << "Ошибка при создании таблицы: " << e.what() << std::endl;
        std::cout << "\033[0m";
        throw; // Пробрасываем исключение дальше
    }
}

void MovieStorage::addMovie(const std::string& name, const std::string& genre, 
    const std::string& watch_date, int rating) {
    pqxx::work txn(*conn);
    txn.exec("INSERT INTO " + txn.quote_name(_table_name) 
        + " (name, genre, watch_date, rating) VALUES (" 
        + txn.quote(name) + ", " + txn.quote(genre) + ", " 
        + txn.quote(watch_date) + ", " + txn.quote(rating) + ")");
    txn.commit();
}

void MovieStorage::getMovie(int id) {
    pqxx::work txn(*conn);
    pqxx::result res = txn.exec("SELECT * FROM  " + txn.quote_name(_table_name) 
    + "  WHERE id = " + txn.quote(id));

    if (res.empty()) {
        std::cout << "Movie not found!" << std::endl;
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
    pqxx::work txn(*conn);
    txn.exec("UPDATE " + txn.quote_name(_table_name) + " SET name = " 
    + txn.quote(name) + ", genre = " + txn.quote(genre) + ", watch_date = " 
    + txn.quote(watch_date) + ", rating = " + txn.quote(rating) + " WHERE id = " 
    + txn.quote(id));
    txn.commit();
}

void MovieStorage::deleteMovie(int id) {
    pqxx::work txn(*conn);
    txn.exec("DELETE FROM " + txn.quote_name(_table_name) 
    + " WHERE id = " + txn.quote(id));
    txn.commit();
}