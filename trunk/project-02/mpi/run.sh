#!/bin/bash
for sieveSlavesCount in 2 4 8
do
	for palindromeSlavesCount in 2 4 8
	do
		cd src
		make -s clean
		make -s SIEVE_SLAVES_COUNT=$sieveSlavesCount PALINDROME_SLAVES_COUNT=$palindromeSlavesCount
		cd ..
		threads=$[5 + $sieveSlavesCount + $palindromeSlavesCount]
		/usr/bin/time -f "$sieveSlavesCount $palindromeSlavesCount %e" -o run.points -a mpirun -n $threads ./src/main
		echo "Done (sieve/palindrome slaves): $sieveSlavesCount $palindromeSlavesCount"
	done
done
