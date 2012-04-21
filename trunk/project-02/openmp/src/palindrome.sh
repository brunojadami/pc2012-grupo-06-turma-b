#!/bin/bash
for ((threads = 2; threads <= 20; threads++))
do
	for ((size = 1; size <= 41; size += 5))
	do
		make -s N_THREADS=$threads BLOCK_SIZE=$size
		/usr/bin/time -f "$threads $size %e" -o palindrome-small.points -a ./main < small.in
		echo "Done (threads/size): $threads $size"
	done
done
