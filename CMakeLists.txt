cmake_minimum_required(VERSION 4.0)
project(RoyalGameOfUrReloaded)

set(CMAKE_CXX_STANDARD 20)



#find_package(PkgConfig REQUIRED)
#pkg_check_modules(NCURSES ncurses)
#link_libraries(${NCURSES_LIBRARIES})



#Use correct compiler optimization flags on GCC and windows
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE  "-mavx2")
    set(CMAKE_CXX_FLAGS_DEBUG  "-mavx2")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2")
    set(CMAKE_CXX_FLAGS_DEBUG "/Zi /O2")
    set(CMAKE_CXX_FLAGS_RELEASE  "/arch:AVX2")
    set(CMAKE_CXX_FLAGS_DEBUG  "/arch:AVX2")
endif()



#Get your headers from here
include_directories(include)

add_executable(RoyalGameOfUrReloaded src/main.cpp src/board.cpp
        src/player.cpp
        src/playGame.cpp)
