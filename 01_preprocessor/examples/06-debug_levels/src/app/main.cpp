#include<iostream>

int main(int argv, char** argc)
{
#if DEBUG_LEVEL == 0

    std::cout<<"Debugging disabled\n";

#elif DEBUG_LEVEL == 1

    std::cout<<"Basic debugging\n";

#elif DEBUG_LEVEL == 2

    std::cout<<"Verbose debugging\n";

#else

    std::cout<<"Unknown debug level\n";

#endif

    return 0;
}