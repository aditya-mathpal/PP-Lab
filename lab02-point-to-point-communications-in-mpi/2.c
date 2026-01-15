/*
2. Write an MPI program where the master process (process 0) sends a number to each of the slave and the slave processes receive the number and prints it. Use standard send.
*/

#include"mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank == 0) {
        fprintf(stdout, "Enter number: ");
        fflush(stdout);
        scanf("%d", &x);
        for(int i = 1; i < size; i++) {
            fprintf(stdout, "%d sent to process %d\n", x, i);
            fflush(stdout);
            MPI_Send(&x, 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        fprintf(stdout, "%d received by process %d\n", x, rank);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}

/*
output:
$ mpirun -np 6 2.out
Enter number: 73
73 sent to process 1
73 sent to process 2
73 sent to process 3
73 sent to process 4
73 sent to process 5
73 received by process 1
73 received by process 2
73 received by process 3
73 received by process 4
73 received by process 5
*/