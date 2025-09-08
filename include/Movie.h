#include <string>
#include <sstream>
#include <vector>

class Movie {
private:
    std::string name;
    std::string genre;
    std::string watch_date;
    int rating;

public:
    bool linkMovie(std::string& line);

    Movie() = default;

    linkMovie(std::string& line);

    bool checkValid();

};