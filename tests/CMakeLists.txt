set(NAME boids_tests)

add_executable(${NAME})

target_include_directories(${NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${NAME}
    PRIVATE
        src/sense.cpp
        src/vector2d.cpp
)

target_link_libraries(${NAME}
        gtest
        gtest_main
        boids-lib
)

if (CMAKE_VERSION GREATER_EQUAL 3.10)
    gtest_discover_tests(${NAME})
endif()

add_custom_target(${NAME}.run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}.exe
        DEPENDS ${NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        USES_TERMINAL
)