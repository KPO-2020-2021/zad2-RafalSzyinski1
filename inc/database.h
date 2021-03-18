//
// Created by rafik on 15.03.2021.
//

#ifndef COMPLEX_DATABASE_H
#define COMPLEX_DATABASE_H

#include <fstream>
#include <string>

#include "complex.h"

class database
{
private:
    std::ifstream stream;
    std::string difficulty;

    long lines;

    complex<double> first;
    complex<double> second;
    char oper;

    bool open();
public:
    database() = delete;
    explicit database(std::string);
    ~database();

    bool is_open();
    bool eof();

    bool next_equation();
    bool print_equation();
    complex<double> get_answer();
};


#endif //COMPLEX_DATABASE_H
