#! /bin/bash

LIST_FOLDER='mandelbrot_omp mandelbrot_seq mandelbrot_pth'
LIST_LOG=('elephant.log' 'full.log' 'seahorse.log' 'triple_spiral.log')
#LIST_VAR=('task-clock' 'context-switches' 'cpu-migrations' 'page-faults' 'cycles' \'stalled-cycles-frontend' 'stalled-cycles-backend' 'instructions' 'branches' 'branch-misses' 'seconds')
LIST_VAR=('seconds')

for FOLDER in ${LIST_FOLDER}; do
	for LOG in ${LIST_LOG[@]}; do 
		for ITEM in ${LIST_VAR[@]}; do 
			more ${FOLDER}'/'${LOG} | grep ${ITEM} | sed 's/,/./g' | awk '{print $1}' > ${FOLDER}_${LOG}_${ITEM}.dat
		done;	
	done;
done;