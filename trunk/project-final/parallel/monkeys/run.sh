#!/bin/bash

#hosts=node02,node03,node04,node05,node06,node07,node09,node10,node11,node12
hosts=127.0.0.1

for (( i=0; i < 1; i++ ))
do
	for procs in 1 5 10
	do
		for threads in 1 2 4
		do
			make clean
			make release THREADS=$threads
			/usr/bin/time -f "hosts=$procs threads=$threads %e" -o run.out -a mpirun -n $procs --host $hosts ./main < small.in > small.out
			echo "Done: $procs/$threads"
		done
	done
done
