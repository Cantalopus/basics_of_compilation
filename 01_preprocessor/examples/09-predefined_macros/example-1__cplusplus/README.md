# Predefine macros...
```C++
#include <iostream>

#define NUMBER 42

int main()
{
#if __cplusplus >= 202002L

    std::cout<<"C++20 or newer\n";

#elif __cplusplus >= 201703L

    std::cout<<"C++17\n";

#elif __cplusplus >= 201402L

    std::cout<<"C++14\n";

#else

    std::cout<<"Older C++ standard\n";
    
#endif

    return 0;
}
```
### **output**
---
```text
C++20 or newer
```
### **main.i**
```C++
int main()
{
    std::cout<<"C++20 or newer\n";
    return 0;
}
```

