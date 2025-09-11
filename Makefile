GXX = g++
CXXFLAGS = -Iinclude -I/opt/homebrew/include -Wall -Wextra -Werror
SRC = src/main.cpp src/MovieStorage.cpp src/Movie.cpp src/helpers.cpp
TARGET = build/main

all:
	$(GXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)