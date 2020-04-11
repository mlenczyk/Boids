add_subdirectory(SDL2)
add_subdirectory(SDL2_image)

if(enable${name}Tests)
    add_subdirectory(gtest)
endif()