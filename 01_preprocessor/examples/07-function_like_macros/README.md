# Function-like macros... 
Looking at this example, we have:
  
### **main.cpp**
---
```C++
#include<iostream>

#define SQUARE(x) ((x) * (x))

int main()
{
    int number = 5;

    std::cout<<SQUARE(number)<<'\n';
    std::cout<<SQUARE(10)<<'\n';

    return 0;
}
```
We'll compile and run... 
```Bash
g++ main.cpp -o bin/main
./bin/main
```
### **output**:
---
```text
25
100
```
### Look at the preprocessor output
Run:
```Bash
g++ -E -P main.cpp > bin/main.i
```
### **output**:
---
```C++
int main()
{
    int number = 5;
    std::cout<<((number) * (number))<<'\n';
    std::cout<<((10) * (10))<<'\n';
    return 0;
}
```
and, if we replace `x` with `2 + 3`:
```C++
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
```
and then inspect main.i. We'll see:
```C++
int main()
{
    int number = 5;
    std::cout<<number * number<<'\n';
    std::cout<<10 * 10<<'\n';
    std::cout<<5 * 5<<'\n';
    std::cout<<2 +3 * 2 +3<<'\n';
    return 0;
}
```
### **output**:
---
```text
25
100
25
11
```
So, we shouldn't think of `SQUARE()` as a C++ function. Think like the preprocessor here.. it will simply replace `x` with whatever you choose as a substitute. 

