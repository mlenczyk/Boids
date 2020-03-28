set(SDL2_URL https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz)

include(FetchContent)

FetchContent_Declare(
  sdl2
  URL      ${SDL2_URL}
)

FetchContent_MakeAvailable(SDL2)

# set(SDL2_LIBRARY ${FETCHCONTENT_BASE_DIR}/sdl2-src)
# # set(SDL2_INCLUDE_DIR ${FETCHCONTENT_BASE_DIR}/sdl2-src/Include)
# target_compile_definitions(SDL2-static PUBLIC SDL_MAIN_HANDLED)

# SET(SDL2_CONSOLE_OUTPUT_FLAGS "-mconsole")
# target_link_options(SDL2-static PUBLIC ${SDL2_CONSOLE_OUTPUT_FLAGS})