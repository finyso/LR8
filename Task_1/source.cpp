#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include "functions.h"
#include "struc.h"

void menu() {
    std::cout << "--------------------------\n";
    std::cout << "Участники спортивных соревнований\n";
    std::cout << "Выполнил: Финский Павел Владимирович, гр.453502\n";
    std::cout << "--------------------------\n";
}

char chinazes() {
    char choice;
    std::cout << "Хотите запустить программу?(y/n): ";
    std::cin >> choice;

    while(std::cin.peek() != '\n' || choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Неверный ввод, введите y/n: ";
        std::cin >> choice;
    }

    return choice;
}

void action() {
    std::cout << "Меню:\n";
    std::cout << "1. Добавить спортсмена\n";
    std::cout << "2. Просмотреть спортсмена\n";
    std::cout << "3. Заполнить поле на основе других полей\n";
    std::cout << "4. Найти спортсмена по возрасту\n";
    std::cout << "5. Удалить спортсмена\n";
    std::cout << "6. Изменить спортсмена\n";
    std::cout << "7. Сортировать спортсменов по возрасту\n";
    std::cout << "8. Сохранить массив в файл\n";
    std::cout << "9. Выйти\n";
    std::cout << "Ваш выбор: ";
}

void choiceAdd(sportsmanarr& array, int& l, int& b, int& p, char* parr) {
    std::cout << "Вводить определённое кол-во структур или до определённого параметра?(1 или 0): ";
    std::cin.ignore(10000,'\n');
    std::cin >> b;

    while (std::cin.peek() != '\n' || std::cin.fail() || (b != 0 && b != 1)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Неверный ввод. Введите число 1 или 0: ";
        std::cin >> b;
    }

    if (b == 1) {
        std::cout << "Введите количество структур: ";
        std::cin >> l;

        while (std::cin.peek() != '\n' || std::cin.fail() || l <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод. Введите число больше 0: ";
            std::cin >> l;
        }

        array = (sportsmanarr)malloc(l * sizeof(sportsman));
        if (!array) {
            std::cout << "Ошибка выделения.";
            exit(1);
        }
    }else {
        std::cout << "Выберите поле параметра:\n";
        std::cout << "1. Страна\n";
        std::cout << "2. Команда\n";
        std::cout << "3. Имя\n";
        std::cout << "4. Номер\n";
        std::cout << "5. Возраст\n";
        std::cout << "6. Рост\n";
        std::cout << "7. Вес\n";
        std::cout << "Ваш выбор: ";
        std::cin >> p;

        while (std::cin.peek() != '\n' || std::cin.fail() || (p < 1 && p > 7)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод. Введите число от 1 до 7: ";
            std::cin >> p;
        }

        std::cout << "Введите значение параметра: ";
        std::cin.ignore(10000, '\n');
        std::cin.getline(parr, sizeof(parr));
        l = 1;
        array = (sportsmanarr)malloc(l * sizeof(sportsman));
    }
}

void add(sportsmanarr& array, int& size, int& l, int& b, int& p, char* parr, char c) {
    if (size >= l) {
        int n;
        std::cout << "Больше места нету. Сколько ещё структур хотите добавить?: ";
        std::cin >> n;

        while (std::cin.peek() != '\n' || std::cin.fail() || n <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод. Введите число больше 0: ";
            std::cin >> n;
        }

        n += l;

        auto newArray = (sportsmanarr)realloc(array, n * sizeof(sportsman));

        if (!newArray) {
            std::cout << "Ошибка выделения памяти.";
            exit(1);
        }

        array = newArray;
        l = n;

        std::cout << "Массив увеличен до " << l << " элементов.\n";

        return;
    }

    sportsman s{};
    std::cout << "Введите страну: ";
    std::cin >> s.country;
    std::cout << "Введите команду: ";
    std::cin >> s.team;
    std::cout << "Введите имя: ";
    std::cin.ignore(10000, '\n');
    std::cin.getline(s.name, sizeof(s.name));
    std::cout << "Введите номер: ";
    std::cin >> s.number;
    std::cout << "Введите возраст: ";
    std::cin >> s.age;
    std::cout << "Введите рост (см): ";
    std::cin >> s.height;
    std::cout << "Введите вес (кг): ";

    std::string input;
    std::cin >> input;

    if (input.find('.') != std::string::npos) {
        s.weight.d = std::stod(input);
        s.isDouble = true;
    } else {
        s.weight.i = std::stoi(input);
        s.isDouble = false;
    }

    array[size++] = s;

    if (b == 0 && (c == 'n' || c == 'N')) {
        bool match = false;
        switch (p) {
            case 1: match = strcmp(s.country, parr) == 0; break;
            case 2: match = strcmp(s.team, parr) == 0; break;
            case 3: match = strcmp(s.name, parr) == 0; break;
            case 4: match = (std::to_string(s.number) == parr); break;
            case 5: match = (std::to_string(s.age) == parr); break;
            case 6: match = (std::to_string(s.height) == parr); break;
            case 7: match = (std::to_string(s.weight.i) == parr || std::to_string(s.weight.d) == parr); break;
            default: break;
        }

        if (match) {
            std::cout << "Совпадение найдено." << std::endl;
        }else {
            std::cout << "Совпадений не найдено." << std::endl;
            int n = l + 1;
            auto newArray = (sportsmanarr)realloc(array, n * sizeof(sportsman));

            if (!newArray) {
                std::cout << "Ошибка выделения памяти.";
                exit(1);
            }

            array = newArray;
            l = n;
        }
    }
}

bool isCyrillic(char c) {
    return c >= 0x0410 && c <= 0x044F;
}

int getAdjustedWidth(const std::string& str) {
    int width = str.size() + 5;
    for (char c : str) {
        if (isCyrillic(c)) {
            width++;
        }
    }
    return width;
}

void view(sportsmanarr array, int size) {
    if (size == 0) {
        std::cout << "Список спортсменов пуст.\n";
        return;
    }

    std::cout << std::left
              << std::setw(7)  << "№"
              << std::setw(13) << "country"
              << std::setw(9) << "team"
              << std::setw(12) << "number"
              << std::setw(8) << "age"
              << std::setw(11) << "height"
              << std::setw(10) << "weight"
              << std::setw(29) << "name" << '\n';
    std::cout << std::string(100, '-') << '\n';

    for (int i = 0; i < size; ++i) {
        const sportsman& s = array[i];
        std::cout << std::left << std::setw(5)  << (i + 1);
        std::cout << std::left << std::setw(getAdjustedWidth(s.country)) << s.country;
        std::cout << std::left << std::setw(getAdjustedWidth(s.team)) << s.team
                  << std::setw(10) << s.number
                  << std::setw(10) << s.age
                  << std::setw(10) << s.height
                  << std::setw(9) << (s.isDouble ? s.weight.d : s.weight.i);
        std::cout << std::left << std::setw(getAdjustedWidth(s.name)) << s.name << '\n';

    }
}

void fillOther(sportsmanarr array, int size) {
    if (size < 2) {
        std::cout << "Недостаточно структур для выполнения операции.\n";
        return;
    }

    int sourceNum, targetNum;
    std::cout << "Введите игровой номер спортсмена-источника: ";
    std::cin >> sourceNum;
    std::cout << "Введите игровой номер спортсмена-приёмника: ";
    std::cin >> targetNum;

    sportsman* source = nullptr;
    sportsman* target = nullptr;

    for (int i = 0; i < size; ++i) {
        if (array[i].number == sourceNum) {
            source = &array[i];
        }
        if (array[i].number == targetNum) {
            target = &array[i];
        }
    }

    if (!source || !target) {
        std::cout << "Одна из структур с указанным номером не найдена.\n";
        return;
    }

    std::cout << "Выберите поле для копирования:\n";
    std::cout << "1. Страна\n";
    std::cout << "2. Команда\n";
    std::cout << "3. Имя\n";
    std::cout << "4. Номер\n";
    std::cout << "5. Возраст\n";
    std::cout << "6. Рост\n";
    std::cout << "7. Вес\n";
    std::cout << "Ваш выбор: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            strncpy(target->country, source->country, sizeof(target->country));
            std::cout << "Поле 'Страна' скопировано.\n";
            break;
        case 2:
            strncpy(target->team, source->team, sizeof(target->team));
            std::cout << "Поле 'Команда' скопировано.\n";
            break;
        case 3:
            strncpy(target->name, source->name, sizeof(target->name));
            std::cout << "Поле 'Имя' скопировано.\n";
            break;
        case 4:
            target->number = source->number;
            std::cout << "Поле 'Номер' скопировано.\n";
            break;
        case 5:
            target->age = source->age;
            std::cout << "Поле 'Возраст' скопировано.\n";
            break;
        case 6:
            target->height = source->height;
            std::cout << "Поле 'Рост' скопировано.\n";
            break;
        case 7:
            if (source->isDouble) {
                target->weight.d = source->weight.d;
                target->isDouble = true;
                std::cout << "Поле 'Вес (double)' скопировано.\n";
            } else {
                target->weight.i = source->weight.i;
                target->isDouble = false;
                std::cout << "Поле 'Вес (int)' скопировано.\n";
            }
            break;
        default:
            std::cout << "Неверный выбор.\n";
    }
}

void findAge(sportsmanarr array, int size, int age) {
    int flag = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i].age > age) {
            std::cout << "Имя: " << array[i].name << ", Возраст: " << array[i].age << "\n";
            flag = 1;
        }
    }
    if (!flag) {
        std::cout << "Спортсмен не найден.\n";
    }
}

void deleteSportsman(sportsmanarr& array, int& size, int n) {
    bool flag = false;
    for (int i = 0; i < size; ++i) {
        if (array[i].number == n) {
            flag = true;
            for (int j = i; j < size - 1; ++j) {
                array[j] = array[j + 1];
            }
            --size;
            --i;
        }
    }
    if(!flag) std::cout << "Спортсмен не найден.\n";
}

void update(sportsmanarr& array, int size, int n) {
    for (int i = 0; i < size; ++i) {
        if (array[i].number == n) {
            std::cout << "Введите новую страну: ";
            std::cin >> array[i].country;
            std::cout << "Введите новую команду: ";
            std::cin >> array[i].team;
            std::cout << "Введите новое имя: ";
            std::cin.ignore(10000, '\n');
            std::cin.getline(array[i].name, sizeof(array[i].name));
            std::cout << "Введите новый возраст: ";
            std::cin >> array[i].age;
            std::cout << "Введите новый рост (см): ";
            std::cin >> array[i].height;
            std::cout << "Введите новый вес (кг): ";

            std::string input;
            std::cin >> input;

            if (input.find('.') != std::string::npos) {
                array[i].weight.d = std::stod(input);
                array[i].isDouble = true;
            } else {
                array[i].weight.i = std::stoi(input);
                array[i].isDouble = false;
            }
            return;
        }
    }
    std::cout << "Спортсмен не найден.\n";
}

void sortAge(sportsmanarr array, int size) {
    for (int l = size / 2; l > 0; l /= 2) {
        for (int i = l; i < size; ++i) {
            sportsman temp = array[i];
            int j;
            for (j = i; j >= l && array[j - l].age < temp.age; j -= l) {
                array[j] = array[j - l];
            }
            array[j] = temp;
        }
    }
}

void loadFile(sportsmanarr& array, int& size, int& l, const char* file) {
    std::ifstream inFile(file, std::ios::binary);
    if (!inFile) {
        std::cout << "Ошибка открытия файла для чтения.\n";
        return;
    }

    inFile.seekg(0, std::ios::end);
    l = inFile.tellg() / sizeof(sportsman);
    inFile.seekg(0, std::ios::beg);

    array = (sportsmanarr)malloc(l * sizeof(sportsman));
    if (!array) {
        std::cout << "Ошибка выделения памяти.\n";
        exit(1);
    }

    inFile.read(reinterpret_cast<char*>(array), l * sizeof(sportsman));
    if (!inFile) {
        std::cout << "Ошибка чтения из файла.\n";
    } else {
        std::cout << "Данные успешно загружены из файла " << file << ".\n";
    }

    inFile.close();

    size = l;
}

void saveFile(sportsmanarr array, int size, const char* file) {
    std::ofstream outFile(file, std::ios::binary | std::ios::out);
    if (!outFile) {
        std::cout << "Ошибка открытия файла для записи.\n";
        return;
    }

    outFile.write(reinterpret_cast<const char*>(array), size * sizeof(sportsman));
    if (!outFile) {
        std::cout << "Ошибка записи в файл.\n";
    } else {
        std::cout << "Данные сохранены в файл " << file << ".\n";
    }

    outFile.close();
}