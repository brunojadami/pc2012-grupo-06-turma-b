#!/bin/bash
size=15
for ((pThreads = 2; pThreads <= 10; pThreads++))
do
	for ((sThreads = 2; sThreads <= 10; sThreads++))
	do
		cd src
		make -s clean
		make -s release PALINDROME_N_THREADS=$pThreads PALINDROME_BLOCK_SIZE=$size SIEVE_N_THREADS=$sThreads BIG_MAIN=1
		cd ..
		/usr/bin/time -f "$pThreads $sThreads %e" -o run-big.points -a ./src/main < src/big.in
		echo "Done (palindrome/sieve threads): $pThreads $sThreads"
	done
done
