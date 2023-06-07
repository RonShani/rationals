#include "rational.hpp"

#include <stdexcept> //for exceptions thrown
#include <cstdio> //for outputs
#include <cmath> //for roots and rounds
#include <string> //for outputs
#include <iostream> //for outputs
#include <cassert>
#define EPSILON (std::pow(10,-7));
static void swap_int(int &a, int &b);

namespace alg_rational{

//Constructor - recieves two integers as arguments
//raise logic exception if a_denomerator is zero
Rational::Rational(int a_numerator, int a_denomerator)
{
    if (a_denomerator == 0){
        throw std::logic_error("zero denuminator");//use assert from now on
    }
    m_denumerator = a_denomerator;
    m_numerator = a_numerator;
    fix_negative_sign();
}

//Constructor overload - recieves only numerator int, denum is 1
Rational::Rational(int a_numerator)
{
    m_numerator = a_numerator;
    m_denumerator = 1;
}

//Constructor overload - numerator is 0, denum is 1
Rational::Rational()
{
    m_numerator = 0;
    m_denumerator = 1;
}

//prints the number as two numbers division
void Rational::print()
{
    printf("%d/%d", m_numerator, m_denumerator);
}

//returns the value as decimal with floating point
double Rational::value()
{
    assert(m_denumerator != 0);
    return m_numerator/(double)m_denumerator;
}



// reduces the numerator and denomerator to its smallest integers possible
void Rational::reduce()
{
    int smallest = std::min(std::abs(this->m_denumerator), std::abs(this->m_numerator));
    for (int i=smallest; i>1; i--){
        if (std::abs(this->m_denumerator) % i == 0 && std::abs(this->m_numerator) % i == 0){
            *this = Rational(this->m_numerator/i,this->m_denumerator/i);
            return;
        }
    }
}

//returns the inverse of the number
void Rational::inverse()
{
    assert(m_numerator != 0);
    *this = Rational(this->m_denumerator, this->m_numerator);
}

void Rational::inverse_using_swap()
{
    assert(m_numerator != 0);
    swap_int(m_numerator, m_denumerator);
}

//returns the multiplication result of the called object with the Rational argument sent
Rational Rational::operator*(Rational const& a_fraction)
{
    int numerator = a_fraction.m_numerator*this->m_numerator;
    int denumerator = a_fraction.m_denumerator*this->m_denumerator;
    return Rational(numerator,denumerator);
}

//multiplies self by the Rational argument sent
void Rational::operator*=(Rational const& a_fraction)
{
    *this = *this * a_fraction;
}

//returns the division result of the called object with the Rational argument sent
Rational Rational::operator/(Rational const &a_fraction)
{
    assert(a_fraction.m_numerator*this->m_denumerator != 0);
    int denumerator = a_fraction.m_numerator*this->m_denumerator;
    int numerator = a_fraction.m_denumerator*this->m_numerator;
    return Rational(numerator,denumerator);
}

//divides self by the Rational argument sent
void Rational::operator/=(Rational const &a_fraction)
{
    *this = *this/a_fraction;
}

//finds common smallest denomerator
int Rational::get_common_denomerator(Rational a_fraction)
{
    int common = a_fraction.m_denumerator * this->m_denumerator;
    for(int i=2; i < common; i++){
        if (i % this->m_denumerator == 0 && i % a_fraction.m_denumerator == 0){
            return i;
        }
    }
    return common;
}

//normalize thw two fractions to a common denomerator
void Rational::get_them_as_common_denominator(Rational a_fraction, int &a_frac_this, int &a_frac_a)
{
    int common = get_common_denomerator(a_fraction);
    a_frac_this = (common/this->m_denumerator)*this->m_numerator;
    a_frac_a = (common/a_fraction.m_denumerator)*a_fraction.m_numerator;
}


//returns nicely shaped unicode upper-lower string
std::string Rational::get_cout_string()
{
    std::string lows[11] = {"₀","₁","₂","₃","₄","₅","₆","₇","₈","₉","₋"};
    std::string higs[11] = {"⁰","¹","²","³","⁴","⁵","⁶","⁷","⁸","⁹","⁻"};
    std::string out = "";
    if(this->m_numerator < 0){
        out += "-";
    }
    std::string num = std::to_string(std::abs(this->m_numerator));
    std::string denum = std::to_string(std::abs(this->m_denumerator)); 
    for (size_t i=0;i<num.size();i++){
        out += higs[num[i]-'0'];
    }
    out += "/";
    for (size_t i=0;i<denum.size();i++){
        out += lows[denum[i]-'0'];
    }
    return out;
}

//returns true if called object is smaller than the Rational argument sent
//or false otherwise
bool Rational::operator<(const Rational &a_second)
{
    int this_nomerator;
    int other_nomerator;
    this->get_them_as_common_denominator(a_second, this_nomerator, other_nomerator);
    return this_nomerator < other_nomerator;
}

bool Rational::operator>(const Rational &a_second)
{
    int this_nomerator;
    int other_nomerator;
    this->get_them_as_common_denominator(a_second, this_nomerator, other_nomerator);
    return this_nomerator > other_nomerator;
}

bool Rational::operator<=(const Rational &a_second)
{
    return *this < a_second || *this == a_second;
}

bool Rational::operator>=(const Rational &a_second)
{
    return *this > a_second || *this == a_second;
}

//returns true if called object is not equal the Rational argument sent
//or false otherwise
bool operator!=(Rational a_first, Rational a_second)
{
    return !(a_first==a_second);
}

//returns true if called object equals the Rational argument sent
//or false otherwise
bool operator==(Rational a_first, Rational a_second)
{
    Rational gap_between = a_first - a_second;
    double abs_gap = std::abs(gap_between.value());
    return abs_gap < EPSILON;
}

//overload operator for easy cout
std::ostream &operator<<(std::ostream& os, Rational const& obj){
    return os << ((Rational)obj).get_cout_string();
}

//pre increment
Rational &Rational::operator++()
{
    *this += Rational(1,1);
    return *this;
}

//post increment
Rational Rational::operator++(int)
{
    Rational original = *this;
    ++(*this);
    return original;

}

//pre
Rational &Rational::operator--()
{
    *this -= Rational(1,1);
    return *this;
}

//post
Rational Rational::operator--(int)
{
    Rational original = *this;
    --(*this);
    return original;

}
// operator + overloading (add command)
Rational Rational::operator+(Rational const &obj)
{
    int common = this->get_common_denomerator(obj);
    int this_nomerator = (common/this->m_denumerator)*this->m_numerator;
    int other_nomerator = (common/obj.m_denumerator)*obj.m_numerator;
    return Rational((this_nomerator+other_nomerator),common);
}

//operator += overloading (add command)
void Rational::operator+=(Rational const &obj)
{
    *this = *this + obj;
}

Rational Rational::operator-(Rational const &obj)
{
    return *this + ((Rational)obj) * Rational(-1,1);
}

void Rational::operator-=(Rational const &obj)
{
    *this = *this - obj;
}

// move negative sign from denumerator to numerator if needed
void Rational::fix_negative_sign()
{
    if(this->m_numerator > 0 && this->m_denumerator < 0){
        this->m_denumerator *= (-1);
        this->m_numerator *= (-1);    
    }
}

// recieves an array of Rationals and it's size as arguments
// and returns the sum of all as decimal fraction
double sumd(Rational const *a_rational_array, size_t a_size)
{
    Rational rational_sum = sum(a_rational_array, a_size);
    return rational_sum.value();
}

//recieves an array of Rationals and it's size as arguments
//and returns the sum of all Rational fraction reduced to it's smallest fraction
//denomerator as possible
Rational sum(Rational const *a_rational_array, size_t a_size)
{
    Rational sum(0,1);
    if(a_rational_array == NULL){
        return sum;
    }
    for (size_t i=0; i<a_size; i++){
        sum += a_rational_array[i];
    }
    return sum;
}

}//namespace alg_rational

static void swap_int(int &a, int &b)
{
    int temp_int = a;
    a = b;
    b = temp_int;
}
