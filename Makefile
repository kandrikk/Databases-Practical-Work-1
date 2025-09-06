GXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -Werror
SRC = src/main.cpp src/movies.cpp src/database_movies.cpp
INCLUDE = include/database_movies.h include/movies.h
TARGET = build/main

all:
	$(GXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(INCLUDE)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)

