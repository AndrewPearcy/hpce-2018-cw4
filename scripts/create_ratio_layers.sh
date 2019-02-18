#!/bin/bash
mkdir ratio
cat /dev/urandom | head -c 500 > ratio/random500.bin
P="1 10 50 100 500 1000 5000 10000 50000"
	for j in $P; do
#    mkdir -p ratio
    		bin/generate_sparse_layer 500 ${j} > ratio/n500_${j}.bin;
        	
	done 
