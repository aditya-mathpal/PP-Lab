/*
2. Write an MPI program to read value of N in the root process. Using N processes, including root, find out 1! + (1+2) + 3! + (1+2+3+4) + 5! + (1+2+3+4+5+6) + ... and print the result in the root process.
*/

#include"mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, x, y;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank == 0) {
        fprintf(stdout, "Enter N: ");
        fflush(stdout);
        scanf("%d", x);
    }
}