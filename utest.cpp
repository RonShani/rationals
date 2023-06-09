#include <cstdio>
#include <iostream>
#include <stdlib.h>

#include "rational.hpp"
using namespace alg_rational;

void Fail()
{
    std::cout << "...\033[1;31mFailed\033[0m\n";
}
void Pass()
{
    std::cout << "...\033[1;32mPassed\033[0m\n";
}
void Title(std::string a_message)
{
    std::cout << "\n\033[1;34m"<< a_message <<"\033[0m\n";
}
int test_create()
{
    int fails = 0;
    try{
        Rational res = Rational(1, 0);
        std::cout << "\n" << res << "\n";
        fails++;
    }
    catch (std::logic_error &e){
        std::cout << "\n" << e.what();
    }
    Rational one(1);
    Rational zero(0,1);
    Rational no_args;
    std::cout <<"\ncreated: "<< zero << one << no_args <<" ...";
    if (zero == one){
        fails++;
        Fail();
    }
    if (no_args == one || zero != no_args){
        fails++;
    }
    return fails;
}

int test_add()
{
    int fails = 0;
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational zero;
    Rational result = qrtr + half;
    std::cout << "\n" << qrtr << " + " << half << " == " << result;
    if(Rational(3,4)!=result){
        fails++;
    }
    result = zero+zero;
    std::cout << "\n" << zero << " + " << zero << " == " << result;
    if(Rational(0,1)!=result){
        fails++;
    }
    result = zero+half;
    std::cout << "\n" << zero << " + " << half << " == " << result;
    if(Rational(1,2)!=result){
        fails++;
    }
    return fails;
}

int test_add_to()
{
    int fails = 0;
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational zero;
    std::cout << "\n" << qrtr << " += " << half << " == ";
    qrtr += half;
    std::cout << qrtr;
    if(Rational(3,4)!=qrtr){
        fails++;
    }
    return fails;
}

int test_print()
{
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational zero;
    Rational negative_both(-21,-105);
    Rational negative_numerator(-21,105);
    Rational negative_denumerator(21,-105);
    try{
        std::cout << "quarter: "<<qrtr<<" half: " << half << " zero: "<<zero<<"\n";
        std::cout << "negative_both: "<<negative_both<<"\nnegative_numerator: " << negative_numerator << "\nnegative_denumerator: "<<negative_denumerator<<"\n";
        return 0;
    }
    catch(std::error_code &e){
        return 1;
    }
    return 1;
}
int test_reduce()
{
    int fails = 0;
    Rational qrtr(1,-4);
    Rational half(1,2);
    Rational third(3,9);
    Rational zero;
    Rational negative_both(-20,105);
    std::cout << qrtr << " reduced to ==> ";
    qrtr.reduce();
    std::cout << qrtr << "\n";
    if(Rational(-1,4)!=qrtr){
        fails++;
    }
    std::cout << half << " reduced to ==> ";
    half.reduce();
    std::cout << half << "\n";
    if(Rational(1,2)!=half){
        fails++;
    }
    std::cout << third << " reduced to ==> ";
    third.reduce();
    std::cout << third << "\n";
    if(Rational(1,3)!=third){
        fails++;
    }
    std::cout << zero << " reduced to ==> ";
    zero.reduce();
    std::cout << zero << "\n";
    if(Rational(0,3)!=zero){
        fails++;
    }
    std::cout << negative_both << " reduced to ==> ";
    negative_both.reduce();
    std::cout << negative_both << "\n";
    if(Rational(-4,21)!=negative_both){
        fails++;
    }
    return fails;
}

int test_mult()
{
    int fails = 0;
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational zero;
    Rational negative(20,-105);
    Rational result = qrtr *half;
    std::cout << "\n" << qrtr << " * " << half << " == " << result;
    if(Rational(1,8)!=result){
        fails++;
    }
    result = zero*zero;
    std::cout << "\n" << zero << " * " << zero << " == " << result;
    if(Rational(0,1)!=result){
        fails++;
    }
    result = half*negative;
    std::cout << "\n" << half << " * " << negative << " == " << result;
    if(Rational(-20,210)!=result){
        fails++;
    }
    return fails;
}

int test_div()
{
    int fails = 0;
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational zero;
    Rational negative(20,-105);
    Rational result = qrtr/half;
    std::cout << "\n" << qrtr << " : " << half << " == " << result;
    if(Rational(1,2) != result){
        fails++;
    }
    /* tested ok
    try{
        result = half.div(zero);
        fails++;
    }
    catch(std::io_errc &e){
        std::cout << e << "\n";
    }
    */
    result = zero/half;
    std::cout << "\n" << zero << " : " << half << " == " << result;
    if(Rational(0,1)!=result){
        fails++;
    }
    result = half/negative;
    std::cout << "\n" << half << " : " << negative << " == " << result;
    if(Rational(-105,40)!=result){
        fails++;
    }
    return fails;
}

int test_inverse()
{
    int fails = 0;
    Rational qrtr(1,-4);
    Rational half(1,2);
    Rational third(3,9);
    Rational zero;
    Rational negative_both(-20,105);
    std::cout << negative_both << " inverse to ==> ";
    negative_both.inverse();
    std::cout << negative_both << "\n";
    if(Rational(-105,20)!=negative_both){
        fails++;
    }
    std::cout << half << " inverse to ==> ";
    half.inverse();
    std::cout << half << "\n";
    if(Rational(2,1)!=half){
        fails++;
    }
    std::cout << third << " inverse to ==> ";
    third.inverse();
    std::cout << third << "\n";
    if(Rational(9,3)!=third){
        fails++;
    }
/*  tested ok
    try{
        std::cout << zero << " inverse to ==> ";
        zero.inverse();
        fails++;
    }
    catch(std::io_errc &e){
        std::cout << e << "\n";
    }
*/
    std::cout << qrtr << " inverse to ==> ";
    qrtr.inverse();
    std::cout << qrtr << "\n";
    if(Rational(-4,1)!=qrtr){
        fails++;
    }
    return fails;
}
int test_sub()
{
    int fails = 0;
    Rational qrtr(1,4);
    Rational half(1,2);
    Rational negative(-20,105);
    Rational zero;
    Rational result = qrtr-half;
    std::cout << "\n" << qrtr << " - " << half << " == " << result;
    if(Rational(-1,4)!=result){
        fails++;
    }
    result = zero-negative;
    std::cout << "\n" << zero << " - " << negative << " == " << result;
    if(Rational(20,105)!=result){
        fails++;
    }
    result = negative-half;
    std::cout << "\n" << negative << " - " << half << " == " << result;
    if(Rational(-145,210)!=result){
        fails++;
    }
    return fails;
}

int test_equal_to(Rational a_fraction_a, Rational a_fraction_b)
{
    std::cout <<"test_equal_to:"<< a_fraction_a <<" == "<< a_fraction_b<<" ? "<< (a_fraction_a == a_fraction_b) <<"\n";
    return a_fraction_a==a_fraction_b;
}

void test_swap()
{
    Rational qrtr(1,4);
    Rational half(1,2);
    std::cout << "\ninversing using swap method: " << qrtr << " ==> ";
    qrtr.inverse_using_swap();
    std::cout << qrtr <<"\n";
}
int test_plus_plus_operator()
{
    int fails = 0;
    Rational qrtr(1,-4);
    Rational half(1,2);
    Rational third(3,9);
    Rational zero;
    Rational negative_both(-20,105);
    std::cout << qrtr << " ++ ==> ";
    ++qrtr;
    std::cout << qrtr << "\n";
    if(Rational(3,4)!=qrtr){
        fails++;
    }
    std::cout << qrtr << "--post ==> ";
    qrtr--;
    std::cout << qrtr << "\n";
    if(Rational(-1,4)!=qrtr){
        fails++;
    }
    std::cout << " --pre " << qrtr << " ==> ";
    --qrtr;
    std::cout << qrtr << "\n";
    if(Rational(-5,4)!=qrtr){
        fails++;
    }
    std::cout << half << " ++ to ==> ";
    ++half;
    std::cout << half << "\n";
    if(Rational(3,2)!=half){
        fails++;
    }
    std::cout << third << " ++ to ==> ";
    third++;
    std::cout << third << "\n";
    if(Rational(4,3)!=third){
        fails++;
    }
    std::cout << zero << " ++ to ==> ";
    zero++;
    std::cout << zero << "\n";
    if(Rational(1,1)!=zero){
        fails++;
    }
    return fails;
}
Rational test_sum()
{
    Rational rational_numbers[4] = {Rational(1,4), Rational(1,8), Rational(-1,16), Rational(10,2)};
    Rational sum_result = sum(rational_numbers, 4);
    int i=0;
    std::cout << rational_numbers[i++] <<" + ";
    std::cout << rational_numbers[i++] <<" + ";
    std::cout << rational_numbers[i++] <<" + ";
    std::cout << rational_numbers[i++] <<" == "<< sum_result;
    return sum_result;
}
int main()
{
    Rational ten(20, 2);
    Rational quarter(1, -4);
    Rational two_and_a_half(5, 2);
    int fails = 0;
    int this_test_fail = 0;
    Title("constructor test");
    if((fails = test_create())){
        Fail();
    }
    else{
        Pass();
    }
    Title("testing +");
    if((this_test_fail = test_add())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing +=)");
    if((this_test_fail = test_add_to())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing ++");
    if((this_test_fail = test_plus_plus_operator())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing -");
    if((this_test_fail = test_sub())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing print");
    if((this_test_fail = test_print())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    } 
    Title("testing reduce");
    if((this_test_fail = test_reduce())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }  
    Title("testing *");
    if((this_test_fail = test_mult())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing /");
    if((this_test_fail = test_div())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    Title("testing inverse");
    if((this_test_fail = test_inverse())){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    } 

    int results_array[] = {0,1,0,0,1};
    int results_recieved[] = {
        test_equal_to(Rational(2,8),Rational(1,5)),
        test_equal_to(Rational(2,8),Rational(1,4)),
        test_equal_to(Rational(-2,8),Rational(1,4)),
        test_equal_to(Rational(2,-8),Rational(1,4)),
        test_equal_to(Rational(2,-8),Rational(1,-4))
    };
    Title("testing equal_to");
    this_test_fail = 0;
    for (int i=0; i<5; i++){
        if(results_array[i] != results_recieved[i]){
            this_test_fail++;
        }
    }
    if(this_test_fail){
        Fail();
        fails += this_test_fail;
    }
    else{
        Pass();
    }
    test_swap();
    Title("testing sum");
    if(Rational(85,16) != test_sum()){
        Fail();
        fails++;
    }
    else{
        Pass();
    }
    return fails;
}