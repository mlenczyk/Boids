set(NAME boids)

add_executable(${NAME})

target_sources(${NAME} PRIVATE
    src/main.cpp
    src/window.cpp
)

target_include_directories(${NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${NAME}
    PUBLIC
    SDL2-static
)

add_custom_target(${NAME}.run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}.exe
    DEPENDS ${NAME}
    USES_TERMINAL
)