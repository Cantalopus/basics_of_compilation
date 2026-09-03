#include<iostream>

#define PROGRAM_NAME "debug_mode"
#define VERSION 3

int main(int argc, char** argv)
{
    std::cout<<PROGRAM_NAME<<'\n';
    std::cout<<"Version: "<<VERSION<<'\n';

#ifdef DEBUG_MODE
    std::cout<<"DEBUG_MODE is defined\n";
#endif

#ifndef RELEASE_MODE    
    std::cout<<"RELEASE_MODE is NOT defined\n";
#endif
}