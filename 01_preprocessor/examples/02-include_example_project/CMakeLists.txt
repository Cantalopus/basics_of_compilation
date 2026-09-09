cmake_minimum_required(VERSION 3.31)
project(include_ex CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(
    src 
        ${CMAKE_SOURCE_DIR}/bin
)

target_link_libraries(
    main 
        PRIVATE
            numbers
)

target_compile_features(
    main 
        PRIVATE 
            cxx_std_20
)