set(NAME boids)

add_executable(${NAME})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# # Add SDL2 library
# find_package(SDL2 REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Main)

# # Add SDL2_image library
# find_package(SDL2_image REQUIRED)
# target_link_libraries(${PROJECT_NAME} SDL2::Image)

target_sources(${NAME} PRIVATE
    src/main.cpp
    src/window.cpp
    src/boid.cpp
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

add_custom_command(TARGET ${NAME} POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "E:/Programming/Git/repos/Boids/build/_deps/sdl2-src/x86_64-w64-mingw32/bin/SDL2.dll"      # <--this is in-file
        "E:/Programming/Git/repos/Boids/build/_deps/sdl2_image-src/x86_64-w64-mingw32/bin/SDL2_image.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:${NAME}>)                 # <--this is out-file path