# Debug Mode:
Same basic example from **03_using_preprocessor_directives** except we'll remove the line...
```C++
#define DEBUG_MODE
```
So now we have:
```C++
#include<iostream>

#define PROGRAM_NAME "Preprocessor Experiment"
#define VERSION 3 

int main(int argv, char** argc)
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
```
Now we can compile normally:
```Bash
g++ main.cpp -o main
```
run with:
```Bash
g++ main.cpp -o main
```
We won't see the debug message.  
  
But now we try:
```Bash
g++ -DDEBUG_MODE main.cpp -o main
```
run with... 
```Bash
../../bin/main
```
Now, we should see the message... 
```text
DEBUG_MODE is defined
```
This happens because
```Bash
-DDEBUG_MODE
```
essentially tells the preprocessor:
```C++
#define DEBUG_MODE
```
before it processes `main.cpp`.  

We can prove it with:
```Bash
g++ -DDEBUG_MODE -E main.cpp > ../build/main.i
```  
## Why this is useful... 
Imagine that your source code contains
```C++
#ifdef DEBUG_MODE
    std::cout<<"x = "<<x<<'\n';
#endif
```
You wouldn't necessarily want to keep changing the source code:
```C++
#define DEBUG_MODE     // add this
//#define DEBUG_MODE   // remove this
#define DEBUG_MODE     // add it again... 
```
Instead, the build can decide. 
```text
                  main.cpp
                     │
             ┌───────┴────────┐
             │                │
      g++ -DDEBUG_MODE       g++
             │                │
             ▼                ▼
      DEBUG_MODE exists   DEBUG_MODE
                             absent
             │                │
             ▼                ▼
       debug code kept    debug code
                           removed
```
And there is a connect to CMake here as well... 
```cmake
target_compile_definitions(my_program
    PRIVATE
        DEBUG_MODE
)
```
CMake can ultimately arrange for the compiler to recieve something equivalent to:
```Bash
-DDEBUG_MODE
```
So `target_compile_definitions()` isn't creating some strange CMake-specific DEBUG_MODE concept. It's controlling preprocessor definitions used when compiling a target.  
  
That connection is worth experimenting with next, especially because we can inspect `compile_commands.json` and see what CMake actually handed over to GCC. 