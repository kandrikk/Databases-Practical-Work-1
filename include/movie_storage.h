#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <memory>

class MovieStorage {
public:
    MovieStorage(const std::string& table_name, const std::string& db_name, 
        const std::string& user, const std::string& password, const std::string& host, 
        const std::string& port);

    void new_collection(const std::string& table_name);

    void addMovie(const std::string& name, const std::string& genre, 
        const std::string& watch_date, int rating);

    void getMovie(int id);

    void getAllMovies();

    void updateMovie(int id, const std::string& name, const std::string& genre, 
        const std::string& watch_date, int rating);

    void deleteMovie(int id);

private:
    void connect();
    int count_movies_in_databases();
    void createTable();
    bool tableExists(const std::string& tableName);
    std::unique_ptr<pqxx::connection> conn;

    std::string _table_name; 
    std::string _db_name; 
    std::string _user;
    std::string _password;
    std::string _host;
    std::string _port;
};