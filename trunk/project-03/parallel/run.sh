#!/bin/bash

procs=5
hosts=127.0.0.1

cd src
make clean
make release
cd ..

for size in 250 500 1000 1500 2000 3000 4000 
do
	/usr/bin/time -f "$size %e" -o run.out -a mpirun -n $procs --host $hosts ./src/main < src/input/matriz$size.txt
	echo "Done: $size"
done
