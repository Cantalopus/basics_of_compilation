# **`#undef`**
We already know that:
```C++ 
#define NUMBER 42
```
defines a macro named `NUMBER`.  
  
`#undef` does the opposite:
```C++
#undef NUMBER
```
It tells the preprocessor:
> **Remove the macro definition for `NUMBER`.  
  
We'll try this:
```C++
#include <iostream>

#define NUMBER 42

int main()
{
    std::cout<<NUMBER<<'\n';

#undef NUMBER

#ifdef NUMBER
    std::cout<<"NUMBER is defined\n";
#else
    std::cout<<"NUMBER is not defined\n";
#endif

    return 0;
}
```
### **output**
---
```text
42
NUMBER is NOT defined.
```
### **main.i**
```C++
int main()
{
    std::cout<<42<<'\n';
    std::cout<<"NUMBER is NOT defined.\n";
    return 0;
}
```