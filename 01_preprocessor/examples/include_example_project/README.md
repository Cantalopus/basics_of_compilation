# Include Example Project:
Line 423: This tiny experiment establishes foundational facts simultaneously:
```text
#include    -> brings another file's contents into preprocessing  

#define     -> macro replacement occurs  
  
g++ -E      -> lets us inspect the result
```

## main.cpp
```C++
#include "numbers.h"

int main()
{
    int number = FAVORITE_NUMBER;
    return number;
}
```
## numbers.h
```C++
#define FAVORITE_NUMBER 42  
```

Then we run the command(Bash):
```Bash
g++ -E main.cpp > build/main.i
```
and inspect:
```Bash
less build/main.i
```

## Output:
```text
# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "main.cpp"
# 1 "numbers.h" 1
# 2 "main.cpp" 2

int main()
{
    int number = 42;
    return number;
}
```