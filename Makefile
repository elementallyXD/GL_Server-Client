CC=g++
CFLAGS=-Wall -Wextra -c -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
BOOSTFLAGS=-lboost_system -lboost_thread -lpthread -pthread -std=c++11

EXECUTABLE_S=server
EXECUTABLE_C=client

all: build_s build_c

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp -o server.o

client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp -o client.o

build_s: server.o
	$(CC) $(BOOSTFLAGS) server.o -o $(EXECUTABLE_S)
  
build_c: client.o
	$(CC) $(BOOSTFLAGS) client.o -o $(EXECUTABLE_C)

clear:
	rm -rf *.o $(EXECUTABLE_S) $(EXECUTABLE_C)