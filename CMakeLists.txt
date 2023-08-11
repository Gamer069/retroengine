cmake_minimum_required(VERSION 3.10)
project(RetroEngine)

set(CMAKE_CXX_STANDARD 17)

# Define source files
set(SRC_FILES
    src/app.cc
    src/entrypoint.h
    src/logging.cc
    src/pwin.cc
    src/layer_stack.cc
    src/layer.cc
    src/imgui/imgui_renderer.cc
    src/imgui/imgui_layer.cc
    lib/glad/src/glad.c
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/imgui.cpp
)

# Add include directories
include_directories(
    src
    lib/spdlog/include
    lib/glad/include
    lib/imgui
)

# Add GLFW as a subdirectory
add_subdirectory(lib/GLFW)

# Create a shared library (dylib)
add_library(retroengine SHARED ${SRC_FILES})

if (WIN32)
    target_link_libraries(retroengine glfw)
else()
    target_link_libraries(retroengine glfw "-framework OpenGL" dl)
endif()

# Install target
install(TARGETS retroengine DESTINATION /usr/local/lib)

include(sandbox.cmake)
