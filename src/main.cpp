#include "movie_storage.h"

int main() {
    MovieStorage storage("movies", "movie_db", "kandik", "kandik", "127.0.0.1", "5432");

    storage.interface();

    return 0;
}