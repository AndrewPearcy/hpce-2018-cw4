#!/bin/bash
P="1 2 4 8 16 32 64 128 256 512 1024 2048"
for i in $P; do
#    mkdir -p ratio
    	bin/generate_sparse_layer ${i} ${i} > scaling/n${i}_${i}.bin;
done
