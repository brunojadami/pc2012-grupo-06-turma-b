#!/bin/bash
for ((threads = 2; threads <= 20; threads++))
do
	for ((size = 1; size <= 40; size += 5))
	do
		make -s N_THREADS=$threads BLOCK_SIZE=$size
		/usr/bin/time -f "$threads $size %e" ./main < small.in
	done
done
