#include <pqxx/pqxx>
#include <iostream>
#include <string>

class MovieStorage {
public:
    MovieStorage(const std::string& db_name, const std::string& user, const std::string& password, const std::string& hostaddr, const std::string& port) {
        std::string connection_str = "dbname=" + db_name + " user=" + user + " password=" + password + " hostaddr=" + hostaddr + " port=" + port;
        conn = std::make_unique<pqxx::connection>(connection_str);
    }

    void addMovie(const std::string& name, const std::string& genre, const std::string& watch_date, int rating) {
        pqxx::work txn(*conn);
        txn.exec("INSERT INTO movies (name, genre, watch_date, rating) VALUES (" + txn.quote(name) + ", " + txn.quote(genre) + ", " + txn.quote(watch_date) + ", " + txn.quote(rating) + ")");
        txn.commit();
    }

    void getMovie(int id) {
        pqxx::work txn(*conn);
        pqxx::result res = txn.exec("SELECT * FROM movies WHERE id = " + txn.quote(id));
        if (res.empty()) {
            std::cout << "Movie not found!" << std::endl;
        } else {
            for (const auto& row : res) {
                std::cout << "ID: " << row[0] << ", Name: " << row[1] << ", Genre: " << row[2] << ", Date: " << row[3] << ", Rating: " << row[4] << std::endl;
            }
        }
    }

    void updateMovie(int id, const std::string& name, const std::string& genre, const std::string& watch_date, int rating) {
        pqxx::work txn(*conn);
        txn.exec("UPDATE movies SET name = " + txn.quote(name) + ", genre = " + txn.quote(genre) + ", watch_date = " + txn.quote(watch_date) + ", rating = " + txn.quote(rating) + " WHERE id = " + txn.quote(id));
        txn.commit();
    }

    void deleteMovie(int id) {
        pqxx::work txn(*conn);
        txn.exec("DELETE FROM movies WHERE id = " + txn.quote(id));
        txn.commit();
    }

private:
    std::unique_ptr<pqxx::connection> conn;
};

int main() {
    MovieStorage storage("movie_db", "your_username", "your_password", "127.0.0.1", "5432");
    std::string command;
    
    while (true) {
        std::cout << "Enter command (ADD, GET, UPDATE, DELETE, EXIT): ";
        std::getline(std::cin, command);
        
        if (command == "ADD") {
            std::string name, genre, date;
            int rating;
            std::cout << "Enter name, genre, date (YYYY-MM-DD), rating: ";
            std::cin >> name >> genre >> date >> rating;
            storage.addMovie(name, genre, date, rating);
        } else if (command == "GET") {
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            storage.getMovie(id);
        } else if (command == "UPDATE") {
            int id, rating;
            std::string name, genre, date;
            std::cout << "Enter ID, name, genre, date (YYYY-MM-DD), rating: ";
            std::cin >> id >> name >> genre >> date >> rating;
            storage.updateMovie(id, name, genre, date, rating);
        } else if (command == "DELETE") {
            int id;
            std::cout << "Enter ID: ";
            std::cin >> id;
            storage.deleteMovie(id);
        } else if (command == "EXIT") {
            break;
        }
        std::cin.ignore(); // Очистка буфера
    }
    return 0;
}