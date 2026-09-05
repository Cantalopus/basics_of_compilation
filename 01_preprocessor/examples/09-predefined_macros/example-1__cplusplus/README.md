# Predefine macros...
```C++
int main()
{
    std::cout<<NUMBER<<'\n';

    std::cout<<"Files "<<__FILE__<<'\n';
    std::cout<<"Lines: "<<__LINE__<<'\n';
    std::cout<<"Compiled on: "<<__DATE__<<'\n';
    std::cout<<"Compiled at: "<<__TIME__<<'\n';

    return 0;
}
```
### **output**
---
```text
201703
```
### **main.i**
```C++
int main()
{
    std::cout<<201703L<<'\n';

    return 0;
}
```
For other version of `C++` we'll see:
> -std=c++11  ->  201103  

> -std=c++14  ->  201402  

> -std=c++17  ->  201703  

> -std=c++20  ->  202002  

> -std=c++20  ->  202100  

