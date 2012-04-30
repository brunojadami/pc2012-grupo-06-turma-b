#!/bin/bash
for ((sieveSlavesCount = 2; sieveSlavesCount <= 8; sieveSlavesCount++))
do
	for ((palindromeSlavesCount = 2; palindromeSlavesCount <= 8; palindromeSlavesCount++))
	do
		cd src
		make -s SIEVE_SLAVES_COUNT=$sieveSlavesCount PALINDROME_SLAVES_COUNT=$palindromeSlavesCount
		cd ..
		threads=$[5 + $sieveSlavesCount + $palindromeSlavesCount]
		/usr/bin/time -f "$sieveSlavesCount $palindromeSlavesCount %e" -o run.points -a mpirun -n $threads ./src/main
		echo "Done (sieve/palindrome slaves): $sieveSlavesCount $palindromeSlavesCount"
	done
done
