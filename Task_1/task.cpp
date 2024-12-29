#include "functions.h"

int main() {
    menu();

    char choice = chinazes();

    if (choice == 'n' || choice == 'N') {
        std::cout << "Спасибо за использование!";
        return 1;
    }

    do {
        int size{0}, l, b, p;
        char parr[50], ff[100], c;

        sportsmanarr array = nullptr;

        std::cout << "Хотите загрузить бинарный файл?(y/n): ";
        std::cin >> c;

        while(std::cin.peek() != '\n' || c != 'y' && c != 'Y' && c != 'n' && c != 'N') {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод, введите y/n: ";
            std::cin >> c;
        }

        if (c == 'y' || c == 'Y') {
            std::cout << "Введите имя файла: ";
            std::cin.ignore(10000, '\n');
            std::cin >> ff;
            loadFile(array, size, l, ff);
        }else choiceAdd(array, l, b, p, parr);

        int vyb;

        do {
            action();

            std::cin >> vyb;

            switch (vyb) {
                case 1: add(array, size, l, b, p, parr, c); break;
                case 2: view(array, size); break;
                case 3: {
                    fillOther(array, size);
                    break;
                }
                case 4: {
                    int n;
                    std::cout << "Введите возраст: ";
                    std::cin >> n;
                    findAge(array, size, n);
                    break;
                }
                case 5: {
                    int n;
                    std::cout << "Введите игровой номер для удаления: ";
                    std::cin >> n;
                    deleteSportsman(array, size, n);
                    break;
                }
                case 6: {
                    int n;
                    std::cout << "Введите игровой номер для обновления ";
                    std::cin >> n;
                    update(array, size, n);
                    break;
                }
                case 7: sortAge(array, size); break;
                case 8: {
                    char file[100];
                    std::cout << "Введите имя файла для сохранения: ";
                    std::cin >> file;
                    saveFile(array, size, file);
                    break;
                }
                case 9: break;
                default: std::cout << "Неверный ввод.\n";
            }
        } while (vyb != 9);

        free(array);

        choice = chinazes();
    }while(choice == 'y' || choice == 'Y');
    std::cout << "Спасибо за использование!";
    return 0;
}