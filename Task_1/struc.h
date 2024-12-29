#ifndef STRUC_H
#define STRUC_H

typedef struct{
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
}sportsman;

#endif
