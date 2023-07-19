SRC=src/
BIN=bin/
LIB=lib/
CC=g++
CCFLAGS=-g -I$(SRC) -w -I$(LIB)spdlog/include/ -I$(LIB)glfw/include/ -I$(LiB)glfw/include/glfw -std=c++17 -lglfw -framework OpenGL

.PHONY: all build path clean

all: clean build

build:
	$(CC) $(CCFLAGS) -c $(SRC)app.cc -o $(BIN)app.o
	$(CC) $(CCFLAGS) -c $(SRC)sandbox/sandbox_app.cc -o $(BIN)sandbox_app.o
	$(CC) $(CCFLAGS) -c $(SRC)entrypoint.h -o $(BIN)entrypoint.o
	$(CC) $(CCFLAGS) -c $(SRC)logging.cc -o $(BIN)logging.o
	$(CC) $(CCFLAGS) -c $(SRC)pwin.cc -o $(BIN)pwin.o
	
	$(CC) $(CCFLAGS) $(BIN)app.o $(BIN)sandbox_app.o $(BIN)logging.o $(BIN)pwin.o -o $(BIN)retroengine
	rm -rf $(BIN)retroengine.dSYM

clean:
	rm -rf $(BIN)
	mkdir $(BIN)
	rm -rf /usr/local/bin/retroengine

path:
	cp ./bin/retroengine /usr/local/bin/retroengine
	