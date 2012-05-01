#!/bin/bash
for ((threads = 1; threads <= 256; threads *= 2))
do
	cd src
	make -s clean
	make SIEVE_THREADS=$threads SIEVE_MAIN=1
	cd ..
	/usr/bin/time -f "$threads %e" -o sieve.points -a ./src/main
	echo "Done (threads): $threads"
done
