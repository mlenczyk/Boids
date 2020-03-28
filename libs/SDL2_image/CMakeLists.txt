set(SDL2_IMAGE_URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz)

include(FetchContent)

FetchContent_Declare(
  sdl2_image
  URL      ${SDL2_IMAGE_URL}
)

# FetchContent_GetProperties(SDL2_image)
# if(NOT SDL2_image_POPULATED)
#     FetchContent_Populate(SDL2_image)
#     add_subdirectory(${SDL2_image_SOURCE_DIR} ${SDL2_image_BINARY_DIR})

#     # file(GLOB_RECURSE gtest_includes LIST_DIRECTORIES false ${SDL2_image_SOURCE_DIR}/*.h)

#     # target_sources(gtest
#     #     PUBLIC
#     #         ${gtest_includes}
#     # )
# endif()

FetchContent_MakeAvailable(SDL2_image)

set(SDL2_image_LIBRARY ${FETCHCONTENT_BASE_DIR}/sdl2_image-src)
set(SDL2_image_INCLUDE_DIR ${FETCHCONTENT_BASE_DIR}/sdl2_image-src)
