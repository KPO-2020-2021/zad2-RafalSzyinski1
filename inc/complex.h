#ifndef COMPLEX_COMPLEX_H
#define COMPLEX_COMPLEX_H

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#define DEC_PLACE 3

template<typename T>
class complex
{
private:
    T rel;
    T img;

public:
    complex();
    explicit complex(T rel_);
    complex(T rel_, T img_);

    T real() const;
    T imag() const;
    constexpr double abs() const;
    constexpr complex conj() const;

    constexpr complex operator+(const complex& cm) const;
    constexpr complex operator-(const complex& cm) const;
    constexpr complex operator*(const complex& cm) const;
    constexpr complex operator/(const complex& cm) const;
    constexpr complex operator/(const T& val) const;

    template<typename U>
    friend constexpr bool operator==(const complex<U>& a, const complex<U>& b);

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const complex<U>& cm);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, complex<U>& cm);
};

template<typename T>
complex<T>::complex() : rel(0), img(0)
{
}

template<typename T>
complex<T>::complex(T rel_) : rel(rel_), img(0)
{
}

template<typename T>
complex<T>::complex(T rel_, T img_) : rel(rel_), img(img_)
{
}

/**
 * @return real part of complex number
 */
template<typename T>
T complex<T>::real() const
{
    return rel;
}

/**
 * @return imaginary part of complex number
*/
template<typename T>
T complex<T>::imag() const
{
    return img;
}

/**
 * @return rounded number std::sqrt((real * real) + (imaginary * imaginary))
*/
template<typename T>
constexpr double complex<T>::abs() const
{
    return std::sqrt((rel * rel) + (img * img));
}

/**
 * @return rounded number std::sqrt((real * real) + (imaginary * imaginary))
*/
template<typename T>
constexpr complex<T> complex<T>::conj() const
{
    return complex<T>(rel, -img);
}

template<typename T>
constexpr complex<T> complex<T>::operator+(const complex<T>& cm) const
{
    complex<T> ret(rel + cm.rel, img + cm.img);
    return ret;
}

template<typename T>
constexpr complex<T> complex<T>::operator-(const complex<T>& cm) const
{
    complex<T> ret(rel - cm.rel, img - cm.img);
    return ret;
}

template<typename T>
constexpr complex<T> complex<T>::operator*(const complex<T>& cm) const
{
    T r, i;
    r = rel * cm.rel;
    r -= img * cm.img;
    i = img * cm.rel;
    i += cm.img * rel;

    complex<T> ret(r, i);
    return ret;
}

template<typename T>
constexpr complex<T> complex<T>::operator/(const complex<T>& cm) const
{
    complex<T> ret = (*this * cm.conj()) / (cm.abs() * cm.abs());
    return ret;
}

template<typename T>
constexpr complex<T> complex<T>::operator/(const T& val) const
{
    if(val == 0)
        throw std::runtime_error("Div by 0");

    complex<T> ret(rel / val, img / val);
    return ret;
}

template<typename T>
constexpr bool operator==(const complex<T>& a, const complex<T>& b)
{
    if (std::abs(a.rel-b.rel) <= std::pow(10, -DEC_PLACE) && std::abs(a.img-b.img) <= std::pow(10, -DEC_PLACE))
        return true;
    return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const complex<T>& cm)
{
    os << "(";
    if (cm.img == 0 && cm.rel == 0)
    {
        os << cm.rel << ")";
        return os;
    }

    if (cm.rel != 0)
    {
        os << cm.rel;

        if (cm.img != 0)
        {
            if (cm.img > 0)
                os << "+";
            else if (cm.img < 0)
                os << "-";

            if (std::abs(cm.img) == 1)
                os << "i";
            else
                os << std::abs(cm.img) << "i";
        }
    }
    else
    {
        if (cm.img == 1)
            os << "i";
        else if (cm.img == -1)
            os << "-i";
        else
            os << cm.img << "i";
    }
    os << ")";
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& ist, complex<T>& cm)
{
    std::string line;
    ist >> line;
    std::stringstream is;
    is << line;

    char checkChar;
    char fba, lba, i;
    T first, last;
    is >> fba;
    is >> checkChar;

    if (checkChar == 'i')
    {
        cm.rel = 0;
        cm.img = 1;
        is >> lba;
        if (fba != '(' || lba != ')')
            throw std::invalid_argument("Bad complex form");

        return ist;
    }
    else if (checkChar == '-')
    {
        is >> i;
        if (i == 'i')
        {
            cm.rel = 0;
            cm.img = -1;

            is >> lba;
            if (fba != '(' || lba != ')')
                throw std::invalid_argument("Bad complex form");

            return ist;
        }

        is.putback(i);
    }

    is.putback(checkChar);
    is >> first >> checkChar;

    if (checkChar == ')')
    {
        cm.rel = first;
        cm.img = 0;

        if (fba != '(')
            throw std::invalid_argument("Bad complex form");

        return ist;
    }
    else if (checkChar == 'i')
    {
        cm.rel = 0;
        cm.img = first;

        is >> lba;
        if (fba != '(' || lba != ')')
            throw std::invalid_argument("Bad complex form");

        return ist;
    }
    else if (checkChar == '+' || checkChar == '-')
    {
        is >> i;
        if (i == 'i')
        {
            is >> lba;
            cm.rel = first;
            if (checkChar == '-')
                cm.img = -1;
            else
                cm.img = 1;

            if (lba != ')' || fba != '(')
                throw std::invalid_argument("Bad complex form");

            return ist;
        }

        is.putback(i);
        is >> last >> i >> lba;

        if (checkChar == '-')
            last = -last;

        if (lba != ')' || fba != '(' || i != 'i')
            throw std::invalid_argument("Bad complex form");

        cm.rel = first;
        cm.img = last;

        return ist;
    }
    else
        throw std::invalid_argument("Bad complex form");

}


#endif //COMPLEX_COMPLEX_H
