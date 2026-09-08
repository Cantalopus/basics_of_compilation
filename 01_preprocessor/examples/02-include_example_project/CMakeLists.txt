cmake_minimum_required(VERSION 3.31)
project(include_ex CXX)

add_subdirectory(src ../bin)

target_link_libraries(main 
    PRIVATE
        numbers
)