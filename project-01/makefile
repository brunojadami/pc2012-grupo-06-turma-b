# Makefile. 
#
# Use 'make' for general debug version.
# Use 'make release' for release version.
# See below the flags for each target:
#

FLAGS=-Wall
CC=g++
	
all: debug

debug: FLAGS += -g -p
release: FLAGS += -s -O2

debug: build
release: build

build: precision gauss borwein monte

precision: precision.cpp 
	$(CC) -c $(FLAGS) precision.cpp -o precision

gauss: gauss.cpp gauss-threaded.cpp
	$(CC) -c $(FLAGS) gauss.cpp -o gauss
	$(CC) -c $(FLAGS) gauss-threaded.cpp -o gauss-threaded
	
borwein: borwein.cpp borwein-threaded.cpp
	$(CC) -c $(FLAGS) borwein.cpp -o borwein
	$(CC) -c $(FLAGS) borwein-threaded.cpp -o borwein-threaded
	
monte: monte.cpp monte-threaded.cpp
	$(CC) -c $(FLAGS) monte.cpp -o monte
	$(CC) -c $(FLAGS) monte-threaded.cpp -o monte-threaded
