#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "helpers.h"

class Movie {
public:
    int id;
    std::string name;
    std::string genre;
    std::string watch_date;
    int rating;

    Movie() = default;
    bool load();
    bool load(int si);
    bool checkValid();
};