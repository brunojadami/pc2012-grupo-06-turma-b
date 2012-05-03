#!/bin/bash
for ((threads = 2; threads <= 20; threads++))
do
	for ((size = 1; size <= 41; size += 5))
	do
		cd src
		make -s clean
		make -s PALINDROME_N_THREADS=$threads PALINDROME_BLOCK_SIZE=$size PALINDROME_MAIN=1
		cd ..
		/usr/bin/time -f "$threads $size %e" -o palindrome-big.points -a ./src/main < src/big.in
		echo "Done (threads/size): $threads $size"
	done
done
