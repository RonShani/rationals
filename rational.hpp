#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <string> //for cout operator overloading

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

    Rational add(Rational a_fraction);
    void add_to(Rational a_fraction);
    
    Rational sub(Rational a_fraction);
    void sub_from(Rational a_fraction);
    
    Rational mul(Rational a_fraction);
    void mul_with(Rational a_fraction);
    
    Rational div(Rational a_fraction);
    void div_by(Rational a_fraction);

    bool less(Rational a_fraction);
    friend bool equal_to(Rational a_first, Rational a_second);
    friend bool not_equal_to(Rational a_first, Rational a_second);


    Rational operator+(Rational const& obj);
    void operator+=(Rational const& obj);

    Rational operator-(Rational const& obj);
    void operator-=(Rational const& obj);

    bool operator==(const Rational& a_the_other_one);

private:
    std::string get_cout_string();
    int get_common_denomerator(Rational a_fraction);
    void get_them_as_common_denominator(Rational a_fraction, int *a_frac_this, int *a_frac_a);
    void fix_negative_sign();
    int m_numerator;
    int m_denumerator;
    friend std::ostream &operator<<(std::ostream& os, Rational const& obj);
};

double sumd(Rational const *a_rational_array, size_t a_size);
Rational sum(Rational const *a_rational_array, size_t a_size);
bool equal_to_without_being_a_friend(Rational a_first, Rational a_second);

#endif

