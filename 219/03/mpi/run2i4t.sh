#! /bin/bash
#
# modificado para fazer os testes também para mandelbrot_mpi
# tamanho de entrada foi fixado para 8192
#
set -o xtrace

MEASUREMENTS=1
ITERATIONS=10
# os testes serão feitos somente para esse tamanho de entrada
INITIAL_SIZE=8192

SIZE=$INITIAL_SIZE

NAMES=('mandelbrot_mpi')

BASE=8

#o nome dos executaveis para cada um dos experimentos.
#NAMES=('mandelbrot_1vm8c' 'mandelbrot_2vm4c' 'mandelbrot_4vm2c' 'mandelbrot_8vm1c')

make
mkdir results

for NAME in ${NAMES[@]}; do

    INSTANCES=2
    THREADS=$((BASE/INSTANCES))
    export OMP_NUM_THREADS=$THREADS

    for ((i=1; i<=$ITERATIONS; i++)); do
            perf stat -r $MEASUREMENTS mpirun -np $INSTANCES -hostfile hostfile2i4t ./$NAME -2.5 1.5 -2.0 2.0 $SIZE $INSTANCES $THREADS >> ${NAME}_${SIZE}_full.log 2>&1
            perf stat -r $MEASUREMENTS mpirun -np $INSTANCES -hostfile hostfile2i4t ./$NAME -0.8 -0.7 0.05 0.15 $SIZE $INSTANCES $THREADS >> ${NAME}_${SIZE}_seahorse.log 2>&1
            perf stat -r $MEASUREMENTS mpirun -np $INSTANCES -hostfile hostfile2i4t ./$NAME 0.175 0.375 -0.1 0.1 $SIZE $INSTANCES $THREADS >> ${NAME}_${SIZE}_elephant.log 2>&1
            perf stat -r $MEASUREMENTS mpirun -np $INSTANCES -hostfile hostfile2i4t ./$NAME -0.188 -0.012 0.554 0.754 $SIZE $INSTANCES $THREADS >> ${NAME}_${SIZE}_triple_spiral.log 2>&1
            #SIZE=$(($SIZE * 2))
    done

    #SIZE=$INITIAL_SIZE
    mv *.log results/.
    rm output.ppm
done
