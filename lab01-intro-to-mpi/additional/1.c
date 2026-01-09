#include"mpi.h"
#include<stdio.h>

int reverse(int x) {
    int res = 0;
    while(x) {
        res = res*10 + x%10;
        x /= 10;
    }
    return res;
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int arr[] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};
    arr[rank%9] = reverse(arr[rank%9]);
    for(int i = 0; i < 9; i++) printf("%d  ", arr[i]);
    printf("\n");
    MPI_Finalize();
    return 0;
}