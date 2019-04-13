cmake_minimum_required(VERSION 3.5)

project(Battleship)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wextra")

find_package(SDL2 REQUIRED)

include_directories(lib ${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS})

# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} `sdl-config --cflags --libs`")

add_executable(bs 
    src/bs.cpp
    src/user.cpp 
    src/field.cpp 
    src/ship.cpp 
    src/position.cpp 
    src/event.cpp 
    src/window.cpp 
    src/surface.cpp
    )

    INCLUDE(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL REQUIRED sdl)

TARGET_LINK_LIBRARIES(bs ${SDL_LIBRARIES} ${SDLIMAGE_LIBRARIES})