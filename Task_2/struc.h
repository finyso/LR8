#ifndef STRUC_H
#define STRUC_H

#include <string>

typedef struct {
    std::string name;
    std::string job;
    bool isDouble;
    int day;
    int month;
    int year;
    union {
        int i;
        double d;
    } number;
}employee;

#endif
