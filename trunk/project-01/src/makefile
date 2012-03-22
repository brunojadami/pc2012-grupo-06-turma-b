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
	rm -rf precision gauss gauss-threaded borwein borwein-threaded monte monte-threaded

debug: FLAGS += -g
release: FLAGS += -s -O3

debug: build
release: build

build: precision gauss borwein monte

# The precision is compiled apart.
precision: precision.cpp 
	$(CC) -Wall -s -O3 precision.cpp -o precision

gauss: gauss.cpp gauss-threaded.cpp
	$(CC) $(FLAGS) gauss.cpp -lgmpxx -lgmp -o gauss
	$(CC) $(FLAGS) gauss-threaded.cpp -lgmpxx -lgmp -lpthread -o gauss-threaded
	
borwein: borwein.cpp borwein-threaded.cpp
	$(CC) $(FLAGS) -lgmpxx -lgmp borwein.cpp -o borwein
	$(CC) $(FLAGS) borwein-threaded.cpp -lgmpxx -lgmp -lpthread -o borwein-threaded
	
monte: monte.cpp monte-threaded.cpp
	$(CC) $(FLAGS) monte.cpp -o monte
	$(CC) $(FLAGS) monte-threaded.cpp -lpthread -o monte-threaded
