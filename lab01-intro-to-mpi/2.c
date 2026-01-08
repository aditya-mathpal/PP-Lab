/*
simple calculator
*/

#include"mpi.h"
#include<stdio.h>

void op(int rank) {
    int a = 15, b = 3;
    if(rank%4 == 0) printf("a + b = %d\n", a+b);
    else if(rank%4 == 1) printf("a - b = %d\n", a-b);
    else if(rank%4 == 2) printf("a * b = %d\n", a*b);
    else printf("a / b = %.2f\n", (float)a/b);
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    op(rank);
    MPI_Finalize();
    return 0;
}

/*
compile:
mpicc 2.c -o 2.out

run:
mpirun -np 4 2.out

output:
a + b = 18
a - b = 12
a * b = 45
a / b = 5.00
*/