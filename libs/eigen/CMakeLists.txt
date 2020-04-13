set(EIGEN_URL https://gitlab.com/libeigen/eigen/-/archive/master/eigen-master.zip)

include(FetchContent)

FetchContent_Declare(
    eigen
    URL ${EIGEN_URL}
)

FetchContent_MakeAvailable(eigen)
