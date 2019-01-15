#!/bin/bash
sortAlgorithms=("selection" "insertion" "bubble" "shell" "merge" "quick")

rm -f *.png

for sortAlgorithm in "${sortAlgorithms[@]}"
do
	gnuplot -e "
		set terminal png ;
		set output 'out.png' ;
		set style data linespoints ;
		set key left top ;
		set logscale x ;
		set logscale y ;
		set xlabel 'N' ;
		set ylabel 't [s]' ;
		plot 'selection.dat' title 'selection', 'insertion.dat' title 'insertion', 'bubble.dat' title 'bubble', 'shell.dat' title 'shell', 'merge.dat' title 'merge', 'quick.dat' title 'quick' ;
	"
done