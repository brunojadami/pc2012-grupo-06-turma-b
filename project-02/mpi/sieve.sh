#!/bin/bash
palindromeSlavesCount=1

for sieveSlavesCount in 1 2 4 10 20 40 80
do
	cd src
	make -s clean
	make -s SIEVE_SLAVES_COUNT=$sieveSlavesCount PALINDROME_SLAVES_COUNT=$palindromeSlavesCount SIEVE_MAIN=1
	cd ..
	threads=$[5 + $sieveSlavesCount + $palindromeSlavesCount]
	/usr/bin/time -f "$sieveSlavesCount %e" -o run.points -a mpirun -n $threads ./src/main
	echo "Done (sieve slaves): $sieveSlavesCount"
done
