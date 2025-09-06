#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <memory>

class MovieStorage {
public:
    MovieStorage(const std::string& db_name, const std::string& user, 
        const std::string& password, const std::string& host, const std::string& port);

    void new_databases(const std::string& db_name);

    void addMovie(const std::string& name, const std::string& genre, 
        const std::string& watch_date, int rating);

    void getMovie(int id);

    void updateMovie(int id, const std::string& name, const std::string& genre, 
        const std::string& watch_date, int rating);

    void deleteMovie(int id);

private:
    std::unique_ptr<pqxx::connection> conn;

    std::string _db_name; 
    std::string _user;
    std::string _password;
    std::string _host;
    std::string _port;
};