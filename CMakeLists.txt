cmake_minimum_required(VERSION 3.3)

project(myapp)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(myapp main.cpp Renderer.cpp VertexBuffer.cpp IndexBuffer.cpp VertexArray.cpp)

target_link_libraries(myapp ${OPENGL_gl_LIBRARY} glfw ${GLEW_LIBRARIES})