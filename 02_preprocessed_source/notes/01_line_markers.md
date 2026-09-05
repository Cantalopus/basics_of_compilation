# Line Markers
Taking another look at our output from:
```Bash
g++  -E main.ccp > main.i
```  
inspecting our output:
```C++
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
We notice something unfamilar, lines of code with a `#` and a `0` or a `1`, `2`, `3`, and a `4`. That is followed by we can correctly assume is a file name. 
```C++
# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "main.cpp"
```
The basic form is:
```text
# <line_numbe> <"file_name"> <flags>
#      1        "numbers.h"     1
```
So:
```text
# 1 "main.cpp"
```
basically means:
> The following text corresponds to line 1 of `main.cpp`.  
  
### **Why does the preprocessor need that?**
Suppose our original file is:
```C++
#include "numbers.h"

int main()
{
    int number = NUMBER;
}
```
After preprocessing, the contents of `numbers.h` are inserted into the translation unit.  
  
Now the compiler is dealing with **one giant preprocessed translation unit, but it still needs to know where everything originally came from.  
  
Otherwise, if there's an error originating from `numbers.h`, how could GCC report:
```text
numbers.h:7: error: ...
```
Those trailing 1 and 2 are flags.  
  
`1` means:
> We are entering a new file.  
  
So:
```C++
# 1 "numbers.h" 1
```
means roughly:
> We're entering `numbers.h`, starting at line 1. 
Then:
```text
# 2 "main.cpp" 2
```
The `2` means:
> We are **returning to a file** after finishing another file.  
   
So visually, what happens was:
```text
main.cpp
   │
   │ #include "numbers.h"
   │
   ├──────────────► numbers.h
   │                 │
   │                 │ preprocess contents
   │                 │
   ◄─────────────────┘
   │
   │ resume at line 2
   ▼
main.cpp
```
And GCC records that journey as:
```text
# 1 "main.cpp"

# 1 "numbers.h" 1
                  ↑
               ENTER

# 2 "main.cpp" 2
               ↑
             RETURN
```
### **What about this?**
```C++
# 0 "<built-in>"
# 0 "<command-line>"
```
Those are **special pseudo-files**. They aren't actual files named `<build-in>` and `<command-line>` sitting on your computer.  
  
`<built-in>` refers to things GCC provides automatically-built-in predefined macros and related preprocessing setup.  
  
`<command-line>` represents preprocessing input originating from the compiler command line.  
  
That should sound familiar to us because we've been doing:
```Bash
g++ -DDEBUG_LEVEL=7 ... 
```
That `-D` definition comes from the command-line, not from `main.cpp`.  
  
Then there's:
```C++
# 1 "/usr/include/stdc-predef.h" 1 3 4
```
That's a header GCC automatically brought into the preprocessing environment.  
  
Those numbers are flags:
```text
1 -> entering a new file
2 -> returning to a file
3 -> following text comes from a system header
4 -> following text should be treated as implicitly wrapped in extern "C"(will discuss this one further down in our notes)
```
We won't necessarily see every flag every time.  
  
So don't read this:
```C++
# 1 "/usr/include/stdc-predef.h" 1 3 4
```
as four separate commands. It's one line marker containing several pieces of metadata:  
```text
# 1 "/usr/include/stdc-predef.h" 1 3 4
  │              │               │ │ │
  │              │               │ │ └─ flag 4
  │              │               │ └─── flag 3
  │              │               └───── flag 1
  │              │
  │              └── source/file
  │
  └── line number
```
Furthermore, you can remove these *line markers* if you'd like, by processing with command-line argument `-P`. Such as:
```C++
g++ -E -P main.cpp
```
`-P` tells GCC:
> Don't generate these *line markers*.  
   
So instead of all this:
```C++
# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
...
# 1 "numbers.h" 1
# 2 "main.cpp" 2

int main()
{
    int number = 42;
    return number;
}
```
you'll get something much cleaner, like:
```C++
int main()
{
    int number = 42;
    return number;
}
```
`-E -P` can be useful for learning what the preprocessor did to our C++ code.  
  
However, we shouldn't think of *line markers* as garbage. They are showing us something useful: **the preprocessed translation unit has lost the physical structure of the original source files, so GCC leaves breadcrumbs describing where the resulting text originally came from. 