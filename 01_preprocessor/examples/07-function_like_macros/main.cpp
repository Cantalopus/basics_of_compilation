#include<iostream>

#define SQUARE(x) ((x) * (x))

int main()
{
    int number = 5;

    int result = SQUARE(++number);

    std::cout<<"number: "<<number<<'\n';
    std::cout<<"result: "<<result<<'\n';

    return 0;
}q