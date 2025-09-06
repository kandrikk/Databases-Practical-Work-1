GXX = g++
OTHER_LIB = -I/opt/homebrew/opt/libpqxx/include -L/opt/homebrew/opt/libpqxx/lib -L/opt/homebrew/opt/libpq/lib 
CXXFLAGS = -std=c++17 $(OTHER_LIB) -Iinclude -Wall -Wextra -Werror
SRC = src/*
INCLUDE = -lpqxx -lpq
TARGET = build/main

all:
	$(GXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(INCLUDE)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)

