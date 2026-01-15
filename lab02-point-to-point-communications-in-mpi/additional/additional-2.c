/*
2. Write an MPI program to read value of N in the root process. Using N processes, including root, find out 1! + (1+2) + 3! + (1+2+3+4) + 5! + (1+2+3+4+5+6) + ... and print the result in the root process.
*/

#include"mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, x, y, n;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank == 0) {
        fprintf(stdout, "Enter N: ");
        fflush(stdout);
        scanf("%d", &n);
        y = 1;
        for(int i = 1; i < n; i++) {
            MPI_Recv(&x, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
            y += x;
        }
        fprintf(stdout, "result: %d\n", y);
        fflush(stdout);
    } else {
        if(rank%2) x = (int)(((rank+2)/2.0)*(rank+1));
        else {
            x = 1;
            for(int i = 2; i <= rank+1; i++) x *= i;
        }
        MPI_Ssend(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

/*
output:
$ mpirun -np 6 2.out
Enter N: 6
result: 161
*/