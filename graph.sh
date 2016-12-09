#! /bin/bash
for i in 1 2 3
do
	python graph.py data/statP1E$i.txt data/statP2E$i.txt data/statP2E$i.txt
done
	
