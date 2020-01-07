cmake_minimum_required(VERSION 3.0.0)
project(SDLBubbles)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-g -Werror -std=c++11")

add_compile_definitions(DEBUG)

include_directories(include/**)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if(WIN32)
    link_directories(libWindows)
endif()
if(APPLE)
    link_directories(libMac)
    set(CMAKE_INSTALL_RPATH "@executable_path")
    set(CMAKE_INSTALL_PREFIX "@executable_path")
endif()
if(UNIX AND NOT APPLE)
    link_directories(libLinux)
endif()

add_executable(
    Build
    src/Main.cpp
)

if(WIN32)
target_link_libraries(Build ${SDL2_LIBRARIES} )
endif()

#[[ old
if(APPLE)
target_link_libraries(Build GLEW glfw3 "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-framework CoreVideo")
file(GLOB LIBRARIES "lib/*.dylib")
endif()

if(UNIX AND NOT APPLE)
target_link_libraries(Build GL GLU GLEW glfw3 X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor ${LIBRARIES})
endif()
]]