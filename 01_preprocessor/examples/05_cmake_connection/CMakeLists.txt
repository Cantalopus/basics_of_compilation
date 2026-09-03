cmake_minimum_required(VERSION 3.26)
project(cmake_connection CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    if(CMAKE_EXPORT_COMPILE_COMMANDS)
        message(STATUS "Exporting compile commands... ") 
    endif() 

add_subdirectory(src bin)