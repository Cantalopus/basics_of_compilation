add_executable(cmake_connection
    main.cpp
)

target_compile_definitions(cmake_connection
    PRIVATE
        DEBUG_MODE
)
