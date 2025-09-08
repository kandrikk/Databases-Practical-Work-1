GXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -Werror
SRC = src/main.cpp src/MovieStorage.cpp
TARGET = build/main

all:
	$(GXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)