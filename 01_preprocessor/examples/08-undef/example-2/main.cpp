#include <iostream>

#define NUMBER 42

int main()
{
    std::cout<<NUMBER<<'\n';

/*block scope*/{ 
#undef NUMBER
}

#ifdef NUMBER
    std::cout<<"NUMBER is defined.\n";
#else
    std::cout<<"NUMBER is NOT defined.\n";
#endif

    return 0;
}