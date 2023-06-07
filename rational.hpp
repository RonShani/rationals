#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <string> //for cout operator overloading

namespace alg_rational{
/*
 * Rational numbers class
    deal numbers as fraction of two numbers*/
class Rational {

public:
    
    Rational(int a_numerator, int a_denomerator);
    Rational(int a_numerator);
    Rational();


    void print(); 
    double value(); 

    void reduce(); 
    void inverse();
    void inverse_using_swap();

    Rational& operator++();
    Rational operator++(int);
    Rational operator--(int);
    Rational& operator--();
    
    Rational operator+(Rational const& obj);
    void operator+=(Rational const& obj);

    Rational operator-(Rational const& obj);
    void operator-=(Rational const& obj);

    Rational operator*(Rational const& a_fraction);
    void operator*=(Rational const& a_fraction);

    Rational operator/(Rational const& a_fraction);
    void operator/=(Rational const& a_fraction);

    bool operator<(const Rational &a_second);
    bool operator>(const Rational &a_second);
    bool operator<=(const Rational &a_second);
    bool operator>=(const Rational &a_second);

private:
    std::string get_cout_string();
    int get_common_denomerator(Rational a_fraction);
    void get_them_as_common_denominator(Rational a_fraction, int &a_frac_this, int &a_frac_a);
    void fix_negative_sign();
    int m_numerator;
    int m_denumerator;
    friend std::ostream &operator<<(std::ostream& os, Rational const& obj);
};

double sumd(Rational const *a_rational_array, size_t a_size);
Rational sum(Rational const *a_rational_array, size_t a_size);
bool operator==(Rational a_first, Rational a_second);
bool operator!=(Rational a_first, Rational a_second);

}
#endif

