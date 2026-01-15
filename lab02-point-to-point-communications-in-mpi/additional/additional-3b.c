/*
3. Implement at least 2 programs to identify deadlock conditions in synchronous send and standard send with multiple point to point communications beteween two processes
*/

#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>

#define n 9999999

int main(int argc, char *argv[]) {
    int rank, size, x, y;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank==0) {
        MPI_Ssend(&x, n, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(&y, n, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
        fprintf(stdout, "process %d received data\n", 0);
        fflush(stdout);
    } else {
        MPI_Ssend(&y, n, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Recv(&x, n, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        fprintf(stdout, "process %d received data\n", 1);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}

/*
output:

*/