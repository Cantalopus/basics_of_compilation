#include<iostream>

#define PROGRAM_NAME "using_preprocessor_directives"
#define VERSION 3

#define DEBUG_MODE
//#define RELEASE_MODE

int main(int argv, char** argc)
{
    std::cout<<PROGRAM_NAME<<'\n';
    std::cout<<"Version: "<<VERSION<<'\n';

#ifdef DEBUG_MODE
    std::cout<<"DEBUG_MODE is defined\n";
#endif

#ifdef RELEASE_MODE
    std::cout<<"RELEASE_MODE is defined\n";
#else 
    std::cout<<"RELEASE_MODE is NOT defined\n";
#endif

    return 0;
}