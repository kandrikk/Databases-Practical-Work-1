#include <iostream>

char menu() {
    char mode;

    std::cout << "1. Выбор коллекции или создание новой\n"
    "2. Добавить фильм\n"
    "3. Найти фильм по id\n"
    "4. Редактировать данные фильма\n"
    "5. Удалить фильм\n"
    "6. Показать все фильмы\n" 
    "7. Выйти\n"
    "\n"
    "Выберите действие: ";

    mode = getchar();
    if (mode < '1' || mode > '7') {
        std::cout << "Некорректный ввод, пожалуйства выберите действие из меню\n\n";
        while (getchar() != '\n');

        mode = menu();
    }

    return mode;
}

int main() {
    char mode = menu();

    std::cout << mode << std::endl;

    return 0;
}