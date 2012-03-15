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
release: FLAGS += -s -O2

debug: build
release: build

build: precision gauss borwein monte

# The precision is compiled apart.
precision: precision.cpp 
	$(CC) -Wall -s -O2 precision.cpp -o precision

gauss: gauss.cpp gauss-threaded.cpp
	$(CC) $(FLAGS) -lgmpxx -lgmp -lrt gauss.cpp -o gauss
	$(CC) $(FLAGS) -lgmpxx -lgmp -lrt gauss-threaded.cpp -o gauss-threaded
	
borwein: borwein.cpp borwein-threaded.cpp
	$(CC) $(FLAGS) borwein.cpp -o borwein
	$(CC) $(FLAGS) borwein-threaded.cpp -o borwein-threaded
	
monte: monte.cpp monte-threaded.cpp
	$(CC) $(FLAGS) monte.cpp -o monte -O3
	$(CC) $(FLAGS) monte-threaded.cpp -lpthread -o monte-threaded -O3
