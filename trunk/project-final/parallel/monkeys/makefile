# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

MPI_COMPILE_FLAGS = $(shell mpiCC --showme:compile)
MPI_LINK_FLAGS = $(shell mpiCC --showme:link) -fopenmp

FLAGS= 
CC=g++

all: debug

lol:
	mpic++ -fopenmp main.cpp -g -O3 -o main

clean: 
	rm -rf *.o main

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: main.o
	$(CC) $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) main.o -o main

main.o: main.cpp
	$(CC) -c $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) main.cpp
	
