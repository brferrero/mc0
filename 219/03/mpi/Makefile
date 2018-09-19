OUTPUT=mandelbrot

IMAGE=.ppm

CC=mpicc
CC_OPT=-std=c11
CC_OMP=-fopenmp

.PHONY: all
all: $(OUTPUT)_mpi

$(OUTPUT)_mpi: $(OUTPUT)_mpi.c
	$(CC) -o $(OUTPUT)_mpi $(CC_OPT) $(CC_OMP) $(OUTPUT)_mpi.c

.PHONY: clean
clean:
	rm $(OUTPUT)_mpi *$(IMAGE)
