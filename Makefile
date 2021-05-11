CC=g++
CFLAGS=-Wall -Wextra -c -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
BOOSTFLAGS=-lboost_system -lboost_thread -lpthread -pthread -std=c++11

EXECUTABLE_S=server
EXECUTABLE_C=client

all: build_s build_c

server.o: server.h server.cpp
	$(CC) $(CFLAGS) server.cpp -o server.o

client.o: client.h client.cpp
	$(CC) $(CFLAGS) client.cpp -o client.o

build_s: server.o main_server.cpp
	$(CC) $(BOOSTFLAGS) server.o main_server.cpp -o $(EXECUTABLE_S)
  
build_c: client.o main_client.cpp
	$(CC) $(BOOSTFLAGS) client.o main_client.cpp -o $(EXECUTABLE_C)

clear:
	rm -rf *.o $(EXECUTABLE_S) $(EXECUTABLE_C)