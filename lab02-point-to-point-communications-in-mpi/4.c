/*
4. Write an MPI program to read an integer value in the root process. Root process sends this value to Process1, Process1 sends this value to Process2 and so on. Last process sends the value back to root process. When sending the value each process will first increment the received value by one. Write the program using point to point communication routines.
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
        fprintf(stdout, "%d sent to process 1\n", x);
        fflush(stdout);
        MPI_Send(&x, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        fprintf(stdout, "%d received by process 0\n", x);
        fflush(stdout);
    } else {
        MPI_Recv(&x, 1, MPI_INT, rank-1, rank, MPI_COMM_WORLD, &status);
        fprintf(stdout, "%d received by process %d\n", x, rank);
        fflush(stdout);
        fprintf(stdout, "%d sent to process %d\n", x, (rank+1)%size);
        fflush(stdout);
        MPI_Send(&x, 1, MPI_INT, (rank+1)%size, (rank+1)%size, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

/*
output:
$ mpirun -np 6 4.out
Enter number: 55
55 sent to process 1
55 received by process 1
55 sent to process 2
55 received by process 2
55 sent to process 3
55 received by process 3
55 sent to process 4
55 received by process 4
55 sent to process 5
55 received by process 5
55 sent to process 0
55 received by process 0
*/