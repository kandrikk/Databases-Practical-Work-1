#include "Movie.h"

bool Movie::linkMovie(std::string& line) {
    std::vector<std::string> param;

    std::istringstream iss(line);
    std::string word;

    while (iss >> word) param.push_back(word);

    if (param.size() != )
}