# CMake Connection...
We'll make a tiny CMake project where we can watch `target_compile_definitions()` **affect the preprocessor**, rather than just speaking of it!  
  
We'll use this structure:
```text
05_cmake_connection/
│
├── CMakeLists.txt
│
└── src/
    ├── CMakeLists.txt
    │
    └── app/
        ├── CMakeLists.txt
        └── main.cpp
```
## `main.cpp`
```C++
#include<iostream>

int main(int argv, char** argc)
{
#ifdef DEBUG_MODE
    std::cout<<"Debug Mode is ON\n";
#else
    std::cout<<"Debug Mode is OFF\n";
#endif

    return 0;
}
```
Notice that there is no:
```C++
#define DEBUG_MODE
```
anywhere in the C++ code.  
  
## `./CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.26)
project(cmake_connection CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    if(CMAKE_EXPORT_COMPILE_COMMANDS)
        message(STATUS "Exporting compile commands... ") 
    endif() 

add_subdirectory(src bin)
```
## `./src/CMakeLists.txt`
```cmake
add_subdirectory(app)
```
## `./src/app/CMakeLists.txt`
```cmake
add_executable(cmake_connection
    main.cpp
)

target_compile_definitions(cmake_connection
    PRIVATE
        DEBUG_MODE
)
```
Now we can configure and build:
```Bash
cmake -S . -b build --fresh
cmake --build build
```
Then run it
```Bash
./build/bin/app/cmake_connection
```
### Output:
```text
Debug mode is ON
```
`DEBUG_MODE` did not come from `main.cpp`.  
  
It came from here:
```cmake
target_compile_definitions(app
    PRIVATE
        DEBUG_MODE
)
```
Now we can look inside:
```Bash
less build/compile_commands.json
```
Ouutput:
```text
[
{
  "directory": "/home/capts/notes/cpp/compilation_model/basics_of_compilation/01_preprocessor/examples/05_cmake_connection/build/bin/app",

  "command": "/usr/bin/c++ -DDEBUG_MODE   -o CMakeFiles/cmake_connection.dir/main.cpp.o -c /home/capts/notes/cpp/compilation_model/basics_of_compilation/01_preprocessor/examples/05_cmake_connection/src/app/main.cpp",

  "file": "/home/capts/notes/cpp/compilation_model/basics_of_compilation/01_preprocessor/examples/05_cmake_connection/src/app/main.cpp",

  "output": "bin/app/CMakeFiles/cmake_connection.dir/main.cpp.o"
}
]
```
and as we can clearly see in our command:
```text
"command": "/usr/bin/c++ -DDEBUG_MODE   -o ...
```
We can go into `./src/app/CMakeLists.txt`and comment out:
```text
# target_compile_definitions(app
#     PRIVATE
#         DEBUG_MODE
# )
```
then:
```Bash
cmake -S . -B build --fresh
cmake --build build
./build/bin/app/cmake_connection
```
Now our output will be:
```text 
Debug Mode is OFF
```
And if we inspect the `./build/compile_commands.json` again, we will see that `-DDEBUG_MODE` will be missing from `command:`  
  
That's the important relationship:
> **CMake isn't processing `#ifdef DEBUG_MODE`. The C++ preprocessor is. CMake is arranging for `DEBUG_MODE` to be defined when preprocessing happens.  