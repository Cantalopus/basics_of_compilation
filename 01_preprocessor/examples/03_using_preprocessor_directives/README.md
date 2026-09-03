# Example 1 - macros and conditional compilation:
```C++
#include<iostream>

#define PROGRAM_NAME "using_prepocessor_directives"
#define VERSION 3

#define DEBUG_MODE 
//#define RELEASE_MODE

int main(int argv, char** argc)
{
    std::cout<<PROGRAM_NAME<<'\n';
    std::cout<<"Version: "<< VERSION<<'\n';

#ifdef DEBUG_MODE
    std::cout<<"DEBUG_MODE is defined\n";
#endif

#ifdef RELEASE_MODE
    std::cout<<"RELEASE_MODE is defined\n"
#else 
    std::cout<<"RELEASE_MODE is NOT defined\n";
#endif

    return 0;
}
```
Compile and run normally:
```Bash
g++ main.cpp -o ../../bin/main
```
then run with...
```Bash
../../bin/main
```  
  
There are several prepocessor concepts in this program:
| Directive  | Meaning                                    |
| ---------- | -------------------------------------------|
| `#include` | Bring in another file's contents           |
| `#define`  | Define a preprocessor macro                |
| `#ifdef`   | Include code if a macro **is defined**     |
| `#ifndef`  | Include code if a macro **is not defined** |
| `#endif`   | End the conditional section                |
  
The important distinction is that:
```C++
#define DEBUG_MODE 
```
does **not** create a C++ variable.  
  
> There is now a macro named `DEBUG_MODE`. 

So this:
```C++
#ifdef DEBUG_MODE

    std::cout<<"DEBUG_MODE is defined\n";

#endif
```
means:
> Preprocessor, only leave this C++ statement in the translation unit > if `DEBUG_MODE` exists.  
  
### Now do the interesting part
We've already been playing with `g++ -E`, so we'll run:
```Bash
g++ -E main.cpp > ../../build/main.i
```
Then:
```Bash
less ../../build/main.i
```  
  
The <iostream> file will make the file enormous, search less with:
```text
/using_preprocessor_directives
```
Around there, you should see this:
```C++
# 2 "main.cpp" 2








# 9 "main.cpp"
int main(int argv, char** argc)
{
    std::cout<<"using_preprocessor_directives"<<'\n';
    std::cout<<"Version: "<<3<<'\n';


    std::cout<<"DEBUG_MODE is defined\n";



    std::cout<<"RELEASE_MODE is defined\n";




    return 0;
}
```
Notice what's gone:
```C++
#define PROGRAM_NAME ...
#define VERSION ...
#define DEBUG_MODE

#ifdef ...
#ifndef ...
#endif
```
And these:
```C++
PROGRAM_NAME
VERSION
```
have been replaced with:
```C++
"using_preprocessor_directives"
3
```
That's the mental model we need to build:
```text
main.cpp
   |
   |  preprocessor
   ▼
main.i
   |
   |  C++ compiler
   ▼
... 