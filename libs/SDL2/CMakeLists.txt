set(SDL2_URL https://www.libsdl.org/release/SDL2-2.0.12.tar.gz)

include(FetchContent)

FetchContent_Declare(
  sdl2
  URL      ${SDL2_URL}
)

FetchContent_MakeAvailable(SDL2)

target_compile_definitions(SDL2-static PUBLIC SDL_MAIN_HANDLED)

SET(SDL2_CONSOLE_OUTPUT_FLAGS "-mconsole")
target_link_options(SDL2-static PUBLIC ${SDL2_CONSOLE_OUTPUT_FLAGS})