#ifndef STRUC_H
#define STRUC_H

#include <string>

struct employee {
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
};

typedef employee* employeearr;

#endif //STRUC_H
