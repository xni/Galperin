#!/bin/bash

for i in {4..10}; do
    echo "for $i neurons"
    cat main.cpp | sed -e "s/NEURONS = 10/NEURONS = $i/" > current.cpp;
    g++ current.cpp -o for_$i
    for j in {1..100}; do
        echo $i.$j
	./for_$i >> log$i.dat;
    done
done