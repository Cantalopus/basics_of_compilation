add_subdirectory(numbers)
add_subdirectory(app)

target_include_directories(numbers
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src/numbers
)