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
    src/imgui/imgui_layer.cc
    src/imgui/imgui_build.cc
    src/render/renderer.cc
    src/render/opengl_render_context.cc
    src/render/opengl_shader.cc
    src/render/opengl_buf.cc
    src/render/buf.cc
    src/render/array.cc
    src/render/opengl_array.cc
	src/pinp.cc
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
