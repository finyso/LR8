#include "functions.h"

int main() {
    menu();

    char choice = chinazes();

    if (choice == 'n' || choice == 'N') {
        std::cout << "Спасибо за использование!";
        return 1;
    }

    do {
        int size{0}, l;
        char c;
        employeearr array = nullptr;

        std::cout << "Хотите загрузить файл?(y/n): ";
        std::cin >> c;

        while(std::cin.peek() != '\n' || c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод, введите y/n: ";
            std::cin >> c;
        }

        if (c == 'n' || c == 'N') {
            std::cout << "Введите количество структур: ";
            std::cin >> l;

            while (std::cin.peek() != '\n' || std::cin.fail() || l <= 0) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Неверный ввод. Введите число больше 0: ";
                std::cin >> l;
            }

            array = new employee[l];
            if (!array) {
                std::cout << "Ошибка выделения";
                return 1;
            }
        }else loadFile(array, size, l);

        int vyb;

        do {
            action();

            std::cin >> vyb;

            switch (vyb) {
                case 1: add(array, size, l); break;
                case 2: view(array, size); break;
                case 3: {
                    std::string name;
                    std::cout << "Введите имя сотрудника для удаления: ";
                    std::cin.ignore(10000, '\n');
                    std::getline(std::cin, name);
                    deleteEmployee(array, size, name);
                    break;
                }
                case 4: {
                    std::string name;
                    std::cout << "Введите имя сотрудника для обновления ";
                    std::cin.ignore(10000, '\n');
                    std::getline(std::cin, name);
                    update(array, size, name);
                    break;
                }
                case 5: sort(array, size); break;
                case 6: saveFile(array, size); break;
                case 7: break;
                default: {
                    std::cout << "Неверный ввод.\n";
                }
            }
        } while (vyb != 7);

        delete[] array;

        choice = chinazes();
    }while(choice == 'y' || choice == 'Y');
    std::cout << "Спасибо за использование!";
    return 0;
}