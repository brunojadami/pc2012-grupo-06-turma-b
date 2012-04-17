#!/bin/bash
for ((threads = 2; threads <= 20; threads++))
do
	for ((size = 4; size <= 37; size++))
	do
		make -s N_THREADS=$threads BLOCK_SIZE=$size
		echo -n "$threads $size "
		/usr/bin/time -f "%e" ./main < small.in
	done
done
