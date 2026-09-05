#include<iostream>

int main(int argv, char** argc)
{
#ifdef DEBUG_MODE
    std::cout<<"Debug Mode is ON\n";
#else
    std::cout<<"Debug Mode is off\n";
#endif

    return 0;
}