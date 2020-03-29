set(SDL2_URL https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz)

include(FetchContent)

FetchContent_Declare(
  sdl2
  URL      ${SDL2_URL}
)

FetchContent_MakeAvailable(SDL2)

set(SDL2_PATH ${FETCHCONTENT_BASE_DIR}/sdl2-src CACHE PATH "SDL2 Path")