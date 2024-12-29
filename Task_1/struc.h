#ifndef STRUC_H
#define STRUC_H

struct sportsman {
    bool isDouble;
    char country[40];
    char team[30];
    char name[60];
    int number;
    int age;
    int height;
    union {
        int i;
        double d;
    } weight;
};

typedef sportsman* sportsmanarr;

#endif //STRUC_H
