#!/bin/bash
size=15
for ((pThreads = 2; pThreads <= 20; pThreads++))
do
	for ((sThreads = 1; sThreads <= 256; sThreads *= 256))
	do
		cd src
		make -s clean
		make -s PALINDROME_N_THREADS=$pThreads PALINDROME_BLOCK_SIZE=$size SIEVE_N_THREADS=$sThreads
		cd ..
		/usr/bin/time -f "$pThreads $sThreads %e" -o palindrome-big.points -a ./src/main < src/big.in
		echo "Done (palindrome/sieve threads): $pThreads $sThreads"
	done
done
