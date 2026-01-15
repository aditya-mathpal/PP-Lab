/*
3. Write an MPI program to read N elements of the array in the root process (process 0) where N is equal to the total number of processes. The root process sends one value to each of the slaves. Let even ranked procss find square of the received element and odd ranked process find cube of received element. Use buffered send.
*/

#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, x;
    int bufsize = 100*(MPI_BSEND_OVERHEAD + sizeof(MPI_INT));
    void *buf = malloc(bufsize);
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    MPI_Buffer_attach(buf, bufsize);
    if(rank == 0) {
        int arr[100];
        fprintf(stdout, "Enter %d numbers: ", size-1);
        fflush(stdout);
        for(int i = 1; i < size; i++) scanf("%d", &arr[i-1]);
        for(int i = 1; i < size; i++) {
            fprintf(stdout, "%d sent to process %d\n", arr[i-1], i);
            fflush(stdout);
            MPI_Bsend(&arr[i-1], 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        fprintf(stdout, "%d received by process %d\n", x, rank);
        fflush(stdout);
        if(rank%2) {
            fprintf(stdout, "Cube of %d is %d\n", x, x*x*x);
            fflush(stdout);
        }
        else {
            fprintf(stdout, "Square of %d is %d\n", x, x*x);
            fflush(stdout);
        }
    }
    MPI_Buffer_detach(buf, &bufsize);
    MPI_Finalize();
    return 0;
}

/*
output:
$ mpirun -np 8 3.out
Enter 7 numbers: 1 2 3 4 5 6 7    
1 sent to process 1
2 sent to process 2
3 sent to process 3
4 sent to process 4
5 sent to process 5
6 sent to process 6
1 received by process 1
Cube of 1 is 1
7 sent to process 7
2 received by process 2
Square of 2 is 4
3 received by process 3
Cube of 3 is 27
4 received by process 4
Square of 4 is 16
6 received by process 6
Square of 6 is 36
5 received by process 5
Cube of 5 is 125
7 received by process 7
Cube of 7 is 343
*/