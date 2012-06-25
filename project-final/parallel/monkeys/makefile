# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

MPI_COMPILE_FLAGS = $(shell mpiCC --showme:compile)
MPI_LINK_FLAGS = $(shell mpiCC --showme:link) -fopenmp

FLAGS=-lpthread -DTHREADS=$(THREADS)
CC=g++

all: debug

clean: 
	rm -rf *.o main

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: main.o info.o random.o runner.o
	$(CC) $(MPI_COMPILE_FLAGS) $(FLAGS) main.o info.o random.o runner.o -o main $(MPI_LINK_FLAGS)

main.o: main.cpp
	$(CC) -c $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) main.cpp
	
random.o: random.cpp random.h
	$(CC) -c $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) random.cpp

info.o: info.cpp info.h
	$(CC) -c $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) info.cpp
	
runner.o: runner.cpp runner.h
	$(CC) -c $(MPI_COMPILE_FLAGS) $(FLAGS) $(MPI_LINK_FLAGS) runner.cpp
