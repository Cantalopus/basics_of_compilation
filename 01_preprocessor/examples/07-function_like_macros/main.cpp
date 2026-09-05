#include<iostream>

#define SQUARE(x) x * x

int main()
{
    int number = 5;

    std::cout<<SQUARE(number)<<'\n';
    std::cout<<SQUARE(10)<<'\n';
    std::cout<<SQUARE(5)<<'\n';
    std::cout<<SQUARE(2 + 3)<<'\n';

    return 0;
}