set(GOOGLETEST_URL https://github.com/google/googletest/archive/release-1.8.1.zip)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL ${GOOGLETEST_URL}
)

FetchContent_MakeAvailable(googletest)
