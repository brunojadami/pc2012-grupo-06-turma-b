# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

ifeq ($(PALINDROME_N_THREADS),)
	PALINDROME_N_THREADS = 2
endif

ifeq ($(PALINDROME_BLOCK_SIZE),)
	PALINDROME_BLOCK_SIZE = 20
endif

ifeq ($(SIEVE_THREADS),)
	SIEVE_THREADS = 4
endif

ifeq ($(PRIME_MAX),)
	PRIME_MAX = 1000000
endif

FLAGS= -fopenmp -DPALINDROME_N_THREADS=$(PALINDROME_N_THREADS) -DPALINDROME_BLOCK_SIZE=$(PALINDROME_BLOCK_SIZE) -DSIEVE_THREADS=$(SIEVE_THREADS) -DPRIME_MAX=$(PRIME_MAX)
CC=g++
	
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
