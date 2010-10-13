#!/bin/bash

for i in {1..15}; do
    echo "for $i neurons"
    cat main.cpp | sed -e "s/NEURONS = 10/NEURONS = $i/" > current.cpp;
    g++ -O3 current.cpp -o for_$i
    for j in {1..300}; do
        echo $i.$j
	./for_$i >> log$i.dat;
    done
done
