#ifndef HEADER_H
#define HEADER_H

#include "struc.h"
#include <iostream>

void menu();
void action();
void choiceAdd(sportsmanarr&, int&, int&, int&, char*);
char chinazes();
void add(sportsmanarr&, int&, int&, int&, int&, char*, char);
bool isCyrillic(char);
int getAdjustedWidth(const std::string&);
void view(sportsmanarr, int);
void fillOther(sportsmanarr, int);
void findAge(sportsmanarr, int, int);
void deleteSportsman(sportsmanarr&, int&, int);
void update(sportsmanarr&, int, int);
void sortAge(sportsmanarr, int);
void loadFile(sportsmanarr&, int&, int&, const char*);
void saveFile(sportsmanarr, int, const char*);

#endif //HEADER_H
