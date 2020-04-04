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
    src/timer.cpp
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
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        USES_TERMINAL
)

IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VERSION x86_64-w64-mingw32)
ELSE (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VERSION i686-w64-mingw32)
ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/${VERSION}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/${VERSION}/bin/SDL2_image.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2_image.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/${VERSION}/bin/libpng16-16.dll"
        $<TARGET_FILE_DIR:${NAME}>/libpng16-16.dll)
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/${VERSION}/bin/libpng16-16.dll"
        $<TARGET_FILE_DIR:${NAME}>/zlib1.dll)