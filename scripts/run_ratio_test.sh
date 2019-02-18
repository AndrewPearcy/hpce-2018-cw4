#!/bin/bash
# The above shows that it is a bash file

# Create a local variable with a list of K values
PS="1 10 50 100 500 1000 5000 10000 50000"
# Iterate over them and print (echo) them
	for j in $PS; do
    		# Run the program with the chosen K, and save to dump_
#		printf "%.3f\n" "$( bc -l <<< "((500 / ${j})")"
		
     		echo $((500/${j}))
		time cat ratio/random500.bin | \
     		bin/run_network ratio/n500_${j}.bin:simple \
   		> results/ratio/dump500_${j}.csv
done

