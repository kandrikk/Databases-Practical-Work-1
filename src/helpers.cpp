#include "helpers.h"

void redMessage(std::string message) {
    std::cout << "\033[31;1m";
    std::cout << message;
    std::cout << "\033[0m";
}

void greenMessage(std::string message) {
    std::cout << "\u001b[32;1m";
    std::cout << message;
    std::cout << "\033[0m";
}