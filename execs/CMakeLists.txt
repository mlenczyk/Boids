set(NAME boids)

add_executable(${NAME})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

target_sources(${NAME} PRIVATE
    src/main.cpp
    src/window.cpp
    src/boid.cpp
    src/vector2d.cpp
    src/texture.cpp
)

target_include_directories(${NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/public
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${NAME}
    PUBLIC
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

add_custom_target(${NAME}.run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}.exe
    DEPENDS ${NAME}
    USES_TERMINAL
)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/x86_64-w64-mingw32/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/x86_64-w64-mingw32/bin/SDL2_image.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2_image.dll)
