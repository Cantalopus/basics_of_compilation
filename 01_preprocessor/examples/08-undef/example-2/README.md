# **`#undef`** *(example 2)*
```C++
int main()
{
    std::cout<<NUMBER<<'\n';

/*block scope*/{
#undef NUMBER
    }

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

    {

    }




    std::cout<<"NUMBER is NOT defined.\n";


    return 0;
}
```