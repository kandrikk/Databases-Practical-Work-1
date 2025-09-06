#include "movie_storage.h"

MovieStorage::MovieStorage(const std::string& db_name, const std::string& user, 
    const std::string& password, const std::string& host, const std::string& port)
    : _db_name(db_name), _user(user), _password(password), _host(host), _port(port) 
{
    std::string connection_str = "dbname=" + _db_name + " user=" + _user 
    + " password=" + _password + " hostaddr=" + _host + " port=" + _port;
    conn = std::make_unique<pqxx::connection>(connection_str);
}

void MovieStorage::new_databases(const std::string& db_name) {
    _db_name = db_name;
    std::string connection_str = "dbname=" + _db_name + " user=" + _user 
    + " password=" + _password + " hostaddr=" + _host + " port=" + _port;
    conn = std::make_unique<pqxx::connection>(connection_str);
}

void MovieStorage::addMovie(const std::string& name, const std::string& genre, 
    const std::string& watch_date, int rating) {
    pqxx::work txn(*conn);
    txn.exec("INSERT INTO movies (name, genre, watch_date, rating) VALUES (" 
        + txn.quote(name) + ", " + txn.quote(genre) + ", " 
        + txn.quote(watch_date) + ", " + txn.quote(rating) + ")");
    txn.commit();
}

void MovieStorage::getMovie(int id) {
    pqxx::work txn(*conn);
    pqxx::result res = txn.exec("SELECT * FROM movies WHERE id = " + txn.quote(id));

    if (res.empty()) {
        std::cout << "Movie not found!" << std::endl;
    } else {
        for (const auto& row : res) {
            std::cout << "\nName: " << row[1].as<std::string>()
                        << ", Genre: " << row[2].as<std::string>()
                        << ", Date: " << row[3].as<std::string>()
                        << ", Rating: " << row[4].as<std::string>()
                        << std::endl;
        }
    }
}

void MovieStorage::updateMovie(int id, const std::string& name, const std::string& genre, 
    const std::string& watch_date, int rating) 
{
    pqxx::work txn(*conn);
    txn.exec("UPDATE movies SET name = " + txn.quote(name) + ", genre = " + txn.quote(genre) + ", watch_date = " + txn.quote(watch_date) + ", rating = " + txn.quote(rating) + " WHERE id = " + txn.quote(id));
    txn.commit();
}

void MovieStorage::deleteMovie(int id) {
    pqxx::work txn(*conn);
    txn.exec("DELETE FROM movies WHERE id = " + txn.quote(id));
    txn.commit();
}