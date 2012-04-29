# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

FLAGS=
CC=mpiCC
	
all: debug

clean: 
	rm -rf *.o main

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: sieve.o palindrome.o parser.o main.o
	$(CC) $(FLAGS) main.o sieve.o palindrome.o parser.o -o main

main.o: main.cpp
	$(CC) -c $(FLAGS) main.cpp

sieve.o: sieve.cpp
	$(CC) -c $(FLAGS) sieve.cpp
	
palindrome.o: palindrome.cpp
	$(CC) -c $(FLAGS) palindrome.cpp
	
parser.o: parser.cpp
	$(CC) -c $(FLAGS) parser.cpp
