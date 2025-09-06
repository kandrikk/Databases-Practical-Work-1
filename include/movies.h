#pragma once

#include <string>
#include <regex>

class Movies {
private:
    int _id;
    std::string _name;
    std::string _genre;
    std::string _watch_date;
    int _rating;
    
public:

    Movies() = default;
    Movies(int id, const std::string &name, const std::string &genre
        , const std::string &watch_date, int &rating);

    int get_id() const;
    std::string get_name() const;
    std::string get_genre() const;
    std::string get_watch_date() const;
    int get_rating() const;

    void set_id(int new_id);
    void set_name(std::string &name);
    void set_genre(std::string &genre);
    void set_watch_date(std::string &date);
    void set_rating(int rating);
};