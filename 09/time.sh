#!/bin/bash
sortAlgorithms=("selection" "insertion" "bubble" "shell" "merge" "quick")
Ns=(10 100 1000 10000 100000)

rm -f out/*.dat

for sortAlgorithm in "${sortAlgorithms[@]}"
do
	cp $sortAlgorithm.h sort.h
	gcc main.c
	for N in "${Ns[@]}"
	do
		./a.out $N 1 >> out/$sortAlgorithm.dat
	done
	rm sort.h
done

cd out/
./draw.sh
