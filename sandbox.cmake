project("sandbox")
add_executable(sandbox src/sandbox/sandbox_app.cc)
target_include_directories(retroengine PRIVATE src lib/spdlog/include lib/glfw/include lib/glad/include lib/imgui)
target_link_libraries(sandbox PRIVATE retroengine)
if (NOT WIN32)
    target_link_libraries(sandbox PRIVATE glfw "-framework OpenGL" "-fsanitize=address" dl)
endif()
