#ifndef HEADER_H
#define HEADER_H

#include "struc.h"
#include "typedf.h"
#include <iostream>

void menu();
void action();
void choiceAdd(sportsmanarr&, int&, int&, int&, char*);
char chinazes();
void add(sportsmanarr&, int&, int&, int&, int&, char*);
bool isCyrillic(char);
int getAdjustedWidth(const std::string&);
void view(sportsmanarr, int);
void fillOther(sportsmanarr, int);
void findAge(sportsmanarr, int, int);
void deleteSportsman(sportsmanarr&, int&, int);
void update(sportsmanarr&, int, int);
void sortAge(sportsmanarr, int);
void loadFile(sportsmanarr&, int&, const char*);
void saveFile(sportsmanarr, int, const char*);
void deleteFile(const char*);
void viewFile(const char*);
void updateFile(const char*, int);
void addFile(const char*);

#endif
