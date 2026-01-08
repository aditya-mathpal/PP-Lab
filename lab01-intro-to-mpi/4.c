/*
Even ranked processes print factorial of the rank.
Odd ranked processes print Fibonacci number
*/

#include"mpi.h"
#include<stdio.h>

void FactOrFib(int x) {
    int r = x;
    if(x%2 == 0) {
        int res = 1;
        while(x>0) {
            res *= x;
            x -= 1;
        }
        printf("Factorial of %d is %d\n", r, res);
    }
    else {
        if(x == 1) {
            printf("Index 1 in Fibonacci series is 1\n");
            return;
        }
        int a = 0, b = 1, c;
        x -= 1;
        while(x--) {
            c = a+b;
            a = b;
            b = c;
        }
        printf("Index %d in Fibonacci series is %d\n", r, c);
    }
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    FactOrFib(rank);
    MPI_Finalize();
    return 0;
}

/*
compile:
mpicc 4.c -o 4.out

run:
mpirun -np 4 4.out

output:
Index 5 in Fibonacci series is 5
Factorial of 6 is 720
Index 3 in Fibonacci series is 2
Factorial of 0 is 1
Index 1 in Fibonacci series is 1
Index 7 in Fibonacci series is 13
Factorial of 4 is 24
Factorial of 2 is 2
*/