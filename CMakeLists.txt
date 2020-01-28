cmake_minimum_required(VERSION 3.15)
project(debug)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include glad)
include_directories(${GLFW_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/glad.c src/graphics/Window.cpp src/graphics/Window.h src/misc/Utils.cpp src/misc/Utils.h src/graphics/Shader.cpp src/graphics/Shader.h src/graphics/Texture2D.cpp src/graphics/Texture2D.h src/game/Game.cpp src/game/Game.h src/graphics/graphics.h src/graphics/Camera.cpp src/graphics/Camera.h src/graphics/Drawable.cpp src/graphics/Drawable.h src/graphics/ArrayObject.cpp src/graphics/ArrayObject.h src/graphics/BufferObject.cpp src/graphics/BufferObject.h)
add_executable(debug ${SOURCE_FILES})
target_link_libraries(debug
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARY} glfw)