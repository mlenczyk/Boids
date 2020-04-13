set(NAME boids)

add_executable(${NAME})    

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(BOIDS_SOURCES
    include/boids/boid.hpp
    include/boids/window.hpp
    include/boids/vector2d.hpp
    include/boids/texture.hpp
    include/boids/timer.hpp

    src/window.cpp
    src/boid.cpp
    src/vector2d.cpp
    src/texture.cpp
    src/timer.cpp
)

target_sources(${NAME} PUBLIC
    src/main.cpp
)

target_link_libraries(${NAME}
    PUBLIC
    boids-testable
)

add_custom_target(${NAME}.run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${NAME}.exe
        DEPENDS ${NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        USES_TERMINAL
)

IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VERSION x64)
ELSE (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(VERSION x86)
ENDIF (CMAKE_SIZEOF_VOID_P EQUAL 8)

add_custom_command(TARGET ${NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/lib/${VERSION}/SDL2.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/lib/${VERSION}/SDL2_image.dll"
        $<TARGET_FILE_DIR:${NAME}>/SDL2_image.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/lib/${VERSION}/libpng16-16.dll"
        $<TARGET_FILE_DIR:${NAME}>/libpng16-16.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_image_PATH}/lib/${VERSION}/zlib1.dll"
        $<TARGET_FILE_DIR:${NAME}>/zlib1.dll)
        
if(enable${name}Tests)
    set(TEST_LIB_NAME ${NAME}-testable)
    add_library(${TEST_LIB_NAME} STATIC)
    target_sources(${TEST_LIB_NAME} PRIVATE
        ${BOIDS_SOURCES}
    )
    
    target_include_directories(${TEST_LIB_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include/
            ${SDL2_INCLUDE_DIR}
            ${SDL2_IMAGE_INCLUDE_DIR}
    )
    
    target_link_libraries(${TEST_LIB_NAME}
        PUBLIC
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARY}
        Eigen3::Eigen
    )
endif()