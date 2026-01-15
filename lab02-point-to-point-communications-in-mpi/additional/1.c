/*
1. Write an MPI program to read N elements of an array in the master process. Let N processes including master process check whether the array values are prime or not.
*/

#include"mpi.h"
#include<stdio.h>
#include<stdlib.h>

int isPrime(int x) {
    if(x==1) return 0;
    for(int i = 2; i*i <= x; i++) if(x%i==0) return 0;
    return 1;
}

void checkPrime(int x) {
    if(isPrime(x)) fprintf(stdout, "%d is prime\n", x);
    else fprintf(stdout, "%d is not prime\n", x);
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    int rank, size, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank == 0) {
        int* arr = (int*)malloc(sizeof(int)*size);
        fprintf(stdout, "Enter %d numbers: ", size);
        fflush(stdout);
        for(int i = 0; i < size; i++) scanf("%d", &arr[i]);
        for(int i = 1; i < size; i++) {
            fprintf(stdout, "%d sent to process %d\n", arr[i], i);
            fflush(stdout);
            MPI_Send(&arr[i], 1, MPI_INT, i, i, MPI_COMM_WORLD);
        }
        checkPrime(arr[0]);
    } else {
        MPI_Recv(&x, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        checkPrime(x);
    }
    MPI_Finalize();
    return 0;
}

/*
output:
$ mpirun -np 6 1.out
Enter 6 numbers: 7 8 9 10 11 12
8 sent to process 1
9 sent to process 2
8 is not prime
9 is not prime
10 sent to process 3
11 sent to process 4
12 sent to process 5
10 is not prime
11 is prime
12 is not prime
7 is prime
*/