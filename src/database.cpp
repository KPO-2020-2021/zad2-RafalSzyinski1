#include "database.h"

#include <iostream>

database::database(std::string difficulty_)
{
    difficulty = std::move(difficulty_);
    lines = 0;
    oper = 0;
    open();
}

database::~database()
{
    stream.close();
}

/**
 * Methode open file form dtb folder
 * @return true if the file opened correctly
 */
bool database::open()
{
    if (difficulty == "latwy")
        stream.open("../dtb/latwe.dat");
    else if(difficulty == "trudny")
         stream.open("../dtb/trudne.dat");
    else
        return false;

    if (!stream.is_open())
        return false;

    return true;
}

/**
 * @return true if some file is opened
 */
bool database::is_open()
{
    return stream.is_open();
}

/**
 * @return false if file is not opened or we rich end of file
 */
bool database::eof()
{
    if (is_open() && !stream.eof())
        return false;
    return true;
}

/**
 * Methode get 2 complex number and operator form file
 * @return true if everything goes fine
 */
bool database::next_equation()
{
    lines++;
    try
    {
        stream >> first;
    }
    catch (std::exception& e)
    {
        std::cerr << "Equation " << lines << ": " << e.what() << std::endl;
        oper = 0;

        try
        {
            stream >> oper;
            stream >> second;
        }
        catch (...)
        {}

        return false;
    }

    try
    {
        stream >> oper;
        stream >> second;
    }
    catch (std::exception& e)
    {
        std::cerr << "Equation " << lines << ": " << e.what() << std::endl;
        oper = 0;
        return false;
    }

    if (oper != '+' && oper != '-' && oper != '*' && oper != '/')
    {
        std::cerr << "Equation " << lines << ": Bad operator" << std::endl;
        oper = 0;
        return false;
    }

    return true;
}

/**
 * Print out equation
 * @return true if everything goes fine
 */
bool database::print_equation()
{
    if (!is_open())
        return false;

    std::cout << "Equation " << lines << ": " << first << " " << oper << " " << second << std::endl;

    return true;
}

/**
 * Methode calculate with the operator form file.
 * Returns first complex form equation if we divide by zero
 * @return complex number after calculate with the operator
 */
complex<double> database::get_answer()
{
    switch (oper)
    {
        case '+':
            return first + second;
            break;
        case '-':
            return first - second;
            break;
        case '*':
            return first * second;
            break;
        case '/':
            try
            {
                return first / second;
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
            break;
    }

    return first;
}