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
        char parr[50], ff[100];

        sportsmanarr array = nullptr;

        choiceAdd(array, l, b, p, parr);

        int vyb;

        do {
            action();

            std::cin >> vyb;

            switch (vyb) {
                case 1: add(array, size, l, b, p, parr); break;
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
                case 9: {
                    char file[100];
                    std::cout << "Введите имя файла для обновления: ";
                    std::cin >> file;
                    int n;
                    std::cout << "Введите номер структуры для обновления: ";
                    std::cin >> n;

                    while (std::cin.peek() != '\n' || std::cin.fail() || n <= 0) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Неверный ввод. Введите число больше 0: ";
                        std::cin >> n;
                    }

                    updateFile(file, n);
                    break;
                }
                case 10: {
                    char file[100];
                    std::cout << "Введите имя файла для удаления: ";
                    std::cin >> file;
                    deleteFile(file);
                    break;
                }
                case 11: {
                    char file[100];
                    std::cout << "Введите имя файла для добавления: ";
                    std::cin >> file;
                    addFile(file);
                    break;
                }
                case 12: {
                    char file[100];
                    std::cout << "Введите имя файла для просмотра: ";
                    std::cin >> file;
                    viewFile(file);
                    break;
                }
                case 0: break;
                default: std::cout << "Неверный ввод.\n";
            }
        } while (vyb != 0);

        free(array);

        choice = chinazes();
    }while(choice == 'y' || choice == 'Y');
    std::cout << "Спасибо за использование!";
    return 0;
}