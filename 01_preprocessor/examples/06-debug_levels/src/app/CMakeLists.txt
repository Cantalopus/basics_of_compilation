add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG_LEVEL=7
)
