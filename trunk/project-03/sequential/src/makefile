# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

FLAGS= 
CC=g++

all: debug

clean: 
	rm -rf *.o main

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: main.o
	$(CC) $(FLAGS) main.o -o main

main.o: main.cpp
	$(CC) -c $(FLAGS) main.cpp
