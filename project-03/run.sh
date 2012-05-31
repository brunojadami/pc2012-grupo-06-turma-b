#!/bin/bash

cd sequential/src
make clean
make release
cd ..
cd ..

cd parallel/src
make clean
make release
cd ..
cd ..

#hosts=node02,node03,node04,node05,node06,node07,node09,node10,node11,node12
hosts=127.0.0.1

for (( i=0; i < 1; i++ ))
do
	for size in 250 500 1000 1500
	do
		/usr/bin/time -f "sequential $size %e" -o run.out -a ./sequential/src/main < sequential/src/input/matriz$size.txt
		echo "Done sequential: $size"
	done

	for procs in 5 10
	do
		for size in 250 500 1000 1500
		do
			/usr/bin/time -f "parallel $procs $size %e" -o run.out -a mpirun -n $procs --host $hosts ./parallel/src/main < parallel/src/input/matriz$size.txt
			echo "Done parallel: $procs $size"
		done
	done
done
