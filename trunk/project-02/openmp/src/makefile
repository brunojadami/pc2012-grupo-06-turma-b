# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

FLAGS= -fopenmp
CC=g++
	
all: debug

clean: 
	rm -rf *.o main

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: crivo palindrome parser main
	$(CC) $(FLAGS) main.o crivo.o palindrome.o parser.o -o main

main: main.cpp
	$(CC) -c $(FLAGS) main.cpp

crivo: crivo.cpp
	$(CC) -c $(FLAGS) crivo.cpp
	
palindrome: palindrome.cpp
	$(CC) -c $(FLAGS) palindrome.cpp
	
parser: parser.cpp
	$(CC) -c $(FLAGS) parser.cpp
