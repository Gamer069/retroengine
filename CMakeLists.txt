cmake_minimum_required(VERSION 3.10)
project(RetroEngine)

set(CMAKE_CXX_STANDARD 17)

# Define source files
file(GLOB SRC_FILES
    "src/*.cc"
    "src/*.h"
    "src/imgui/*.cc"
    "src/imgui/*.h"
    "src/render/*.cc"
    "src/render/*.h"
    "src/render/cam/*.cc"
    "src/render/opengl/*.cc"
    "src/render/opengl/*.h"
    "src/util/*.cc"
    "lib/glad/src/glad.c"
    "lib/imgui/*.cpp"
)

# Add include directories
include_directories(
    src
    lib/spdlog/include
    lib/glad/include
    lib/imgui
    lib/glm
)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# Add GLFW as a subdirectory
add_subdirectory(lib/GLFW)

# Create a shared library (dylib)
add_library(retroengine STATIC ${SRC_FILES}) # was shared before

if (WIN32)
    target_link_libraries(retroengine glfw)
else()
    target_link_libraries(retroengine glfw "-framework OpenGL" dl)
endif()

include(sandbox.cmake)
