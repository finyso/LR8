#ifndef HEADER_H
#define HEADER_H

#include "struc.h"
#include <iostream>

void menu();
void action();
char chinazes();
void add(employeearr&, int&, int&);
bool isCyrillic(char);
int getAdjustedWidth(const std::string&);
void view(employeearr, int);
void deleteEmployee(employeearr&, int&, const std::string&);
void update(employeearr&, int, const std::string&);
void sort(employeearr, int);
void loadFile(employeearr&, int&, int&);
void saveFile(employeearr, int);

#endif //HEADER_H
