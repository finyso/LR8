#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "functions.h"
#include "struc.h"

void menu() {
    std::cout << "--------------------------\n";
    std::cout << "Информация о сотрудниках\n";
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
    std::cout << "1. Добавить сотрудника\n";
    std::cout << "2. Просмотреть сотрудников\n";
    std::cout << "3. Удалить сотрудника\n";
    std::cout << "4. Изменить сотрудника\n";
    std::cout << "5. Сортировать сотрудников по отделам в порядке убывания стажа\n";
    std::cout << "6. Сохранить в текстовый файл\n";
    std::cout << "7. Выйти\n";
    std::cout << "Ваш выбор: ";
}

void add(employeearr& array, int& size, int& l) {
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

        employeearr newArray = new employee[n];
        std::copy(array, array + size, newArray);

        delete[] array;
        array = newArray;
        l = n;

        std::cout << "Массив увеличен до " << l << " элементов.\n";

        return;
    }

    employee e{};
    std::cout << "Введите имя: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, e.name);
    std::cout << "Введите должность: ";
    std::getline(std::cin, e.job);
    std::cout << "Введите номер отдела: ";

    std::string input;
    std::cin >> input;

    if (input.find('.') != std::string::npos) {
        e.number.d = std::stod(input);
        e.isDouble = true;
    } else {
        e.number.i = std::stoi(input);
        e.isDouble = false;
    }

    std::cout << "Введите год начала работы: ";
    std::cin >> e.year;
    std::cout << "Введите месяц начала работеы: ";
    std::cin >> e.month;
    std::cout << "Введите день начала работы: ";
    std::cin >> e.day;

    array[size++] = e;
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

void view(const employeearr array, int size) {
    if (size == 0) {
        std::cout << "Список сотрудников пуст.\n";
        return;
    }

    std::cout << std::left
              << std::setw(7)  << "№"
              << std::setw(12) << "job"
              << std::setw(12) << "number"
              << std::setw(8) << "day"
              << std::setw(12) << "month"
              << std::setw(10) << "year"
              << std::setw(38) << "name" << '\n';
    std::cout << std::string(100, '-') << '\n';

    for (int i = 0; i < size; ++i) {
        const employee& e = array[i];
        std::cout << std::left
                  << std::setw(5)  << (i + 1);
        std::cout << std::left << std::setw(getAdjustedWidth(e.job)) << e.job
                  << std::setw(12) << (e.isDouble ? e.number.d : e.number.i)
                  << std::setw(10) << e.day
                  << std::setw(10) << e.month
                  << std::setw(10) << e.year
                  << std::setw(40) << e.name << '\n';
    }
}

void deleteEmployee(employeearr& array, int& size, const std::string& name) {
    bool flag = false;
    for (int i = 0; i < size; ++i) {
        if (array[i].name == name) {
            flag = true;
            for (int j = i; j < size - 1; ++j) {
                array[j] = array[j + 1];
            }
            --size;
            --i;
        }
    }
    if (!flag) std::cout << "Сотрудник не найден.\n";
}

void update(employeearr& array, int size, const std::string& name) {
    for (int i = 0; i < size; ++i) {
        if (array[i].name == name) {
            std::cout << "Введите новое имя: ";
            std::getline(std::cin, array[i].name);
            std::cout << "Введите новую должность: ";
            std::getline(std::cin, array[i].job);
            std::cout << "Введите новый номер отдела: ";

            std::string input;
            std::cin >> input;

            if (input.find('.') != std::string::npos) {
                array[i].number.d = std::stod(input);
                array[i].isDouble = true;
            } else {
                array[i].number.i = std::stoi(input);
                array[i].isDouble = false;
            }

            std::cout << "Введите год начала работы: ";
            std::cin >> array[i].year;
            std::cout << "Введите месяц начала работы: ";
            std::cin >> array[i].month;
            std::cout << "Введите день начала работы: ";
            std::cin >> array[i].day;
            return;
        }
    }
    std::cout << "Сотрудник не найден.\n";
}

void sort(employeearr array, int size) {
    employee temp;

    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (array[i].number.i > array[j].number.i) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        int department = array[i].number.i;
        int j = i + 1;

        while (j < size && array[j].number.i == department) {
            ++j;
        }

        for (int k = i; k < j - 1; ++k) {
            for (int l = k + 1; l < j; ++l) {
                if (array[k].year > array[l].year ||
                    (array[k].year == array[l].year && array[k].month > array[l].month) ||
                    (array[k].year == array[l].year && array[k].month == array[l].month && array[k].day > array[l].day)) {
                    temp = array[k];
                    array[k] = array[l];
                    array[l] = temp;
                    }
            }
        }

        i = j - 1;
    }
}

void loadFile(employeearr& array, int& size, int& l) {
    char file[100];
    std::cout << "Введите имя файла для загрузки: ";
    std::cin.ignore(10000, '\n');
    std::cin >> file;
    std::ifstream infile(file);

    if (!infile) {
        std::cout << "Файл не найден. Начинаем с пустого списка.\n";
        return;
    }

    size = 0;
    int n = 1;
    char line[256];
    while (infile.getline(line, sizeof(line))) {
        employeearr newArray = new employee[n];
        std::copy(array, array + size, newArray);

        delete[] array;
        array = newArray;

        char* tokens[10];
        int tokenCount = 0;

        char* token = strtok(line, " ");
        while (token && tokenCount < 10) {
            tokens[tokenCount++] = token;
            token = strtok(nullptr, " ");
        }

        if (tokenCount < 6) {
            std::cout << "Ошибка в формате строки: " << line << '\n';
            continue;
        }

        employee e;

        e.year = std::stoi(tokens[tokenCount - 1]);
        e.month = std::stoi(tokens[tokenCount - 2]);
        e.day = std::stoi(tokens[tokenCount - 3]);

        if (strchr(tokens[tokenCount - 4], '.')) {
            e.isDouble = true;
            e.number.d = std::stod(tokens[tokenCount - 4]);
        } else {
            e.isDouble = false;
            e.number.i = std::stoi(tokens[tokenCount - 4]);
        }

        e.job = tokens[tokenCount - 5];

        e.name = "";
        for (int i = 0; i < tokenCount - 5; ++i) {
            if (i > 0) {
                e.name += " ";
            }
            e.name += tokens[i];
        }

        array[size++] = e;
        n++;
    }

    l = size;

    std::cout << "Массив сотрудников заполнен.\n";
}

void saveFile(const employeearr array, int size) {
    char file[100];
    std::cout << "Введите имя файла для сохранения: ";
    std::cin >> file;
    std::ofstream outfile(file);
    if (!outfile) {
        std::cout << "Ошибка записи в файл.\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        const employee& e = array[i];
        outfile << e.name << " " << e.job << " ";
        if (e.isDouble) {
            outfile << e.number.d;
        } else {
            outfile << e.number.i;
        }
        outfile << " " << e.day << " " << e.month << " " << e.year << "\n";
    }
}