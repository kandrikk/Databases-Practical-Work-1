#include "movies.h"

Movies::Movies(int id, const std::string &name, const std::string &genre
    , const std::string &watch_date, int &rating)
    : _id(id), _name(name), _genre(genre), _watch_date(watch_date), _rating(rating)
{};


int Movies::get_id() const {
    return this->_id;
}

std::string Movies::get_name() const {
    return this->_name;
}

std::string Movies::get_genre() const {
    return this->_genre;
}

std::string Movies::get_watch_date() const {
    return this->_watch_date;
}

int Movies::get_rating() const {
    return this->_rating;
}

void Movies::set_id(int new_id) {
    if (new_id >= 0) this->_id = new_id;
}

void Movies::set_name(std::string &name) {
    if (!name.empty()) this->_name = name;
}

void Movies::set_genre(std::string &genre) {
    if (!genre.empty()) this->_genre = genre;
}

void Movies::set_watch_date(std::string &date) {
    std::regex date_p(R"(\d{4}-\d{2}-\d{2})");
    
    if (!date.empty() && std::regex_match(date, date_p)) this->_watch_date = date;
}

void Movies::set_rating(int new_rating) {
    if (new_rating >= 0 && new_rating <= 10) this->_rating = new_rating;
}
