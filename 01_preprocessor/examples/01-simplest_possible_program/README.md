# Build Directions: 

## Generating build files with CMake:
manually... 
```Bash
cmake -S . -B build 
```
or with presets... 
```Bash
cmake --preset default
```
### Exucute CMake build system:
```Bash
cmake --build build
```  
  
## Using Makefile targets:
Generate executable... 
```Bash
make main
```
Generate `main.i`... 
```Bash
make all
```
## Viewing the contents of `main.i`:
```Bash
less ./build/main.i
```
---
clean `build/` and `bin/` directories with... 
```Bash
make clean
```  
  
# Simplest Possible Program(Exercise):
Suppose we have... 
```c
#define NUMBER 42

int main()
{
    int x = NUMBER;
}
```
We save this as main.cpp(as seen in ../examples).  
  
Normally, we'd do... 
```Bash
g++ main.cpp
```
and GCC quietly performs all the necessary stages... but, we can tell GCC, 'Preprocess this file and then stop', with...  
```Bash
g++ -E main.cpp
``` 
```text
-E       Preprocess only; do not compile, assemble or link.  
```
You'll get quite a bit of output, so it's easier to redirect it:
```Bash
g++ -E main.cpp > main.i
```
the Output will be... 
```text
# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "main.cpp"


int main()
{
    int x = 42;
}
```
Notice what's gone:
```C++
#define NUMBER 42
```
And what's changed:
```C++
int x = NUMBER;
```
became:
```C++
int x = 42;
```  
That's because `#define` is a preprocessor directive  

the C++ compiler never needs to understand `NUMBER` as a C++ variable. The prepocessor dealt with it first.