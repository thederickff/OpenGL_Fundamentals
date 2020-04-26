cmake_minimum_required(VERSION 3.3)

project(myapp)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(./)
include_directories(vendor)

file(GLOB STB_IMG_SRC vendor/stb_image/*.cpp)
file(GLOB IMGUI_SRC vendor/imgui/*.cpp)
file(GLOB SOURCES tests/*.cpp *.cpp)


add_executable(myapp ${STB_IMG_SRC} ${IMGUI_SRC} ${SOURCES})

target_link_libraries(myapp ${OPENGL_gl_LIBRARY} glfw ${GLEW_LIBRARIES})