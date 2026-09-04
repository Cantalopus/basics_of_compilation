# Debug Levels...
Here we introduce the `#if`, numeric macro values, and comparisons without adding much complexity.  
  
Here we have the same basic project structure as `05_cmake_connections`. In `main.cpp` we make these changes:
```C++
#include<iostream>

int main(int argv, char** argc)
{
#if DEBUG_LEVEL == 0

    std::cout<<"Debugging disabled\n";

#elif DEBUG_LEVEL == 1

    std::cout<<"Basic debugging\n";

#elif DEBUG_LEVEL == 2

    std::cout<<"Verbose debugging\n";

#else

    std::cout<<"Unknown debug level\n";

    return 0;
}
```
We also make the appropriate changes to our CMake listfiles. Such as changing all of our target names to `${PROJECT_NAME}. This will allow us to easier copy future examples. 
```cmake
add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG_LEVEL=2
)
```
Then we build while experimenting chaging the `DEBUG_LEVEL` \<number\>. Like, 1, then 0, then 7.  
  
After that, we'll run `g++ -E` again and look at something particularly important: all those other branches literally disappear before C++ compilation begins.  
  
So, our flow chart becomes:
```text
CMakeLists.txt
    │
    │ DEBUG_LEVEL=2
    ▼
compiler command
    │
    │ -DDEBUG_LEVEL=2
    ▼
preprocessor
    │
    │ evaluates:
    │ #if / #elif / #else
    ▼
preprocessed translation unit
    │
    │ only selected branch remains
    ▼
C++ compiler
```
We'll see the same results with:
```C++
g++ -DDEBUG_LEVEL=1 -E src/app/main.cpp > build/main.i
```
In our main.i file we'll see eveything removed from our code with the exeption of:
```C++
std::cout<<"Basic debugging\n";
```
We have the same `main.cpp`, different preprocessed translation unit. 
  