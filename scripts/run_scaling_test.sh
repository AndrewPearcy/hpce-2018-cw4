#!/bin/bash
# The above shows that it is a bash file

# Create a local variable with a list of K values
PS="1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192"
# Iterate over them and print (echo) them
for i in $PS; do
    # Run the program with the chosen K, and save to dump_K.csv
     time cat scaling/random${i}.bin | \
     bin/run_network scaling/n${i}_${i}.bin:simple \
   > results/scaling/dump${i}_${i}.csv

done

