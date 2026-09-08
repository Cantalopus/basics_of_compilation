#include<iostream>

#include "numbers.h"

int main()
{
    int number = FAVORITE_NUMBER;
    
    int a = 20;
    int b = 55;

    std::cout<<"a: "<<a<<'\n';
    std::cout<<"b: "<<b<<'\n';

    std::cout<<"initiate swapping\n";
    a^=b;
    b^=a;
    a^=b;
    std::cout<<"swapping complete!"<<std::endl;

    std::cout<<"a: "<<a<<'\n';
    std::cout<<"b: "<<b<<'\n';
    std::cout<<"number: "<<number<<'\n';

    return 0;
}