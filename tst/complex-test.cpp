#include "complex.h"
#include "gtest/gtest.h"

#include <sstream>

TEST (complex_test, equal)
{
    complex<int> a(1, 2);
    complex<int>b (1, 2);
    EXPECT_EQ(a == b, true);

    complex<int> c(2, 2);
    EXPECT_EQ(a == c, false);
}

TEST (complex_test, contructors)
{
    complex<int> a;
    EXPECT_EQ(a, complex<int>());

    complex<int> b(1);
    EXPECT_EQ(b, complex<int>(1, 0));

    complex<int> c(2, 3);
    EXPECT_EQ(c, complex<int>(2, 3));
}

TEST(complex_test, real_and_imag)
{
    complex<int> a(1, 2);
    EXPECT_EQ(a.real(), 1);
    EXPECT_EQ(a.imag(), 2);
}

TEST(complex_test, add)
{
    complex<int> a(1, 2);
    complex<int> b(2, 3);
    EXPECT_EQ(a + b, complex<int>(3, 5));
}

TEST(complex_test, sub)
{
    complex<int> a(1, 2);
    complex<int> b(2, 3);

    EXPECT_EQ(a - b, complex<int>(-1, -1));
    EXPECT_EQ(b - a, complex<int>(1, 1));
}

TEST(complex_test, multi)
{
    complex<int> a(2, -5);
    complex<int> b(3, 10);

    EXPECT_EQ(a * b, complex<int>(56, 5));
}

TEST(complex_test, abs)
{
    complex<int> a(3, 4);
    EXPECT_EQ(a.abs(), 5);
}

TEST(complex_test, conj)
{
    complex<int> a(3, -5);
    EXPECT_EQ(a.conj(), complex<int>(3, 5));
}

TEST(complex_test, div_by_val)
{
    complex<int> a(4, 8);
    EXPECT_EQ(a / 4, complex<int>(1, 2));

    complex<double> b(5, 10);
    EXPECT_EQ(b / 10, complex<double>(0.5, 1));

    EXPECT_THROW({
                     try
                     {
                         complex<int>(2, 2) / 0;
                     }
                     catch(const std::exception& e)
                     {
                         EXPECT_STREQ("Div by 0", e.what() );
                         throw;
                     }
                 },std::exception);


}

TEST(complex_test, div_by_complex)
{
    complex<int> a(1, 8);
    complex<int> b(2, 3);
    EXPECT_EQ(a / b, complex<int>(2, 1));

    EXPECT_THROW({
                     try
                     {
                         complex<int>(2, 2) / complex<int>(0, 0);
                     }
                     catch(const std::exception& e)
                     {
                         EXPECT_STREQ("Div by 0", e.what() );
                         throw;
                     }
                 },std::exception);
}

TEST(complex_test, ostream)
{
    std::stringstream os;
    complex<int> a(1, 2);
    os << a;
    EXPECT_EQ(os.str(), "(1+2i)");

    complex<int> b(-1, -2);
    os = std::stringstream();
    os << b;
    EXPECT_EQ(os.str(), "(-1-2i)");

    complex<int> c(0, -3);
    os = std::stringstream();
    os << c;
    EXPECT_EQ(os.str(), "(-3i)");

    complex<int> d(-1);
    os = std::stringstream();
    os << d;
    EXPECT_EQ(os.str(), "(-1)");

    complex<int> e(0, -1);
    os = std::stringstream();
    os << e;
    EXPECT_EQ(os.str(), "(-i)");

    complex<int> f(0, 0);
    os = std::stringstream();
    os << f;
    EXPECT_EQ(os.str(), "(0)");

    complex<int> g(2, 1);
    os = std::stringstream();
    os << g;
    EXPECT_EQ(os.str(), "(2+i)");

    complex<int> h(2, -1);
    os = std::stringstream();
    os << h;
    EXPECT_EQ(os.str(), "(2-i)");
}

TEST(complex_test, istream)
{
    std::stringstream is;
    is << "(1+2i)";
    complex<int> a;
    is >> a;
    EXPECT_EQ(a, complex<int>(1, 2));

    is = std::stringstream();
    is << "(-3i)";
    complex<int> b;
    is >> b;
    EXPECT_EQ(b, complex<int>(0, -3));


    is = std::stringstream();
    is << "(-i)";
    complex<int> c;
    is >> c;
    EXPECT_EQ(c, complex<int>(0, -1));

    is = std::stringstream();
    is << "(-2)";
    complex<int> d;
    is >> d;
    EXPECT_EQ(d, complex<int>(-2));

    is = std::stringstream();
    is << "(2+i)";
    complex<int> f;
    is >> f;
    EXPECT_EQ(f, complex<int>(2, 1));

    is = std::stringstream();
    is << "(2-i)";
    complex<int> g;
    is >> g;
    EXPECT_EQ(g, complex<int>(2, -1));

    EXPECT_THROW({
                     try
                     {
                         std::stringstream is2;
                         is2 << "2i";
                         complex<int> e;
                         is2 >> e;
                     }
                     catch(const std::exception& e)
                     {
                         EXPECT_STREQ("Bad complex form", e.what() );
                         throw;
                     }
                 },std::exception);

    EXPECT_THROW({
                     try
                     {
                         std::stringstream is2;
                         is2 << "2137";
                         complex<int> e;
                         is2 >> e;
                     }
                     catch(const std::exception& e)
                     {
                         EXPECT_STREQ("Bad complex form", e.what() );
                         throw;
                     }
                 },std::exception);

    EXPECT_THROW({
                     try
                     {
                         std::stringstream is2;
                         is2 << "asdasdad";
                         complex<int> e;
                         is2 >> e;
                     }
                     catch(const std::exception& e)
                     {
                         EXPECT_STREQ("Bad complex form", e.what() );
                         throw;
                     }
                 },std::exception);
}

TEST (complex_test, double_test)
{
    complex<double> a(3.123, 5.321);
    complex<double> b(-5.321, -3.123);

    EXPECT_DOUBLE_EQ((a + b).imag(), complex<double>(-2.198, 2.198).imag());
    EXPECT_DOUBLE_EQ((a + b).real(), complex<double>(-2.198, 2.198).real());

    EXPECT_DOUBLE_EQ((a - b).imag(), complex<double>(8.444, 8.444).imag());
    EXPECT_DOUBLE_EQ((a - b).real(), complex<double>(8.444, 8.444).real());

    EXPECT_DOUBLE_EQ((a * b).imag(), complex<double>(0, -38.0662).imag());
    EXPECT_DOUBLE_EQ((a * b).real(), complex<double>(0, -38.0662).real());


    EXPECT_DOUBLE_EQ((a / b).imag(), complex<double>(-0.8731, -0.4876).imag());
    EXPECT_DOUBLE_EQ((a / b).real(), complex<double>(-0.8731, -0.4876).real());
}

TEST (complex_test, round_complex)
{
    double a = complex<double>::round_complex(4.312312332);
    EXPECT_DOUBLE_EQ(a, 4.3123);

    complex<double> b(1.1111111111111111111111111111, 1.11111111111111111111111111);
    EXPECT_EQ(complex<double>::round_complex(b), complex<double>(1.1111, 1.1111));

    complex<double> c(111111111111111111111111.1111111111111111111, 111111111111111111111.111111111111111111111);
    EXPECT_EQ(complex<double>::round_complex(c), complex<double>(111111111111111111111111.1111, 111111111111111111111.1111));
}