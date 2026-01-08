#include"mpi.h"
#include<stdio.h>
int main(int argc, char *argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("My rank is %d in total %d processes\n", rank, size);
	MPI_Finalize();
	return 0;
}

/*
compile:
mpicc sample.c -o sample.out

run:
mpirun -np 4 sample.out
or
mpirun -np 32 --oversubscribe sample.out

output:
My rank is 2 in total 4 processes
My rank is 0 in total 4 processes
My rank is 3 in total 4 processes
My rank is 1 in total 4 processes
*/