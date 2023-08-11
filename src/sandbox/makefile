.PHONY: all build run clean make

all: clean build

make: all

build:
	g++ -std=c++17 -dynamiclib -o libretroengine.dylib src/sandbox/sandbox_app.cc -Isrc -Ilib/spdlog/include -Ilib/glfw/include -Ilib/glad/include -Ilib/imgui -Llib/glfw/src -lglfw -Llib/glad/src -ldl -framework OpenGL -fsanitize=address

clean:
	rm -rf libretroengine.dylib

