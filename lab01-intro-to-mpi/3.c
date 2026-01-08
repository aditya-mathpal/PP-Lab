/*
Toggle character of a given string.
Rank of the process is the index of the character to toggle.
*/

#include"mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char str[] = "HELLO";
    str[rank%5] += 32;
    printf("%d: %s\n", rank, str);
    MPI_Finalize();
    return 0;
}

/*
compile:
mpicc 3.c -o 3.out

run:
mpirun -np 5 3.out

output:
0: hELLO
3: HELlO
4: HELLo
1: HeLLO
2: HElLO
*/