# set(SDL2_IMAGE_URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-mingw.tar.gz)
set(SDL2_IMAGE_URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip)


include(FetchContent)

FetchContent_Declare(
  sdl2_image
  URL      ${SDL2_IMAGE_URL}
)

FetchContent_MakeAvailable(SDL2_image)

set(SDL2_image_PATH ${FETCHCONTENT_BASE_DIR}/sdl2_image-src CACHE PATH "SDL2_image Path")
