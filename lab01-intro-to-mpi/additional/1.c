/*
reverse digits of numbers in array
*/

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
    printf("%d reversed: %d  ", arr[rank], reverse(arr[rank]));
    printf("\n");
    MPI_Finalize();
    return 0;
}

/*
output:
325 reversed: 523  
4321 reversed: 1234  
2 reversed: 2  
801 reversed: 108  
51 reversed: 15  
81 reversed: 18  
103 reversed: 301  
41 reversed: 14  
8291 reversed: 1928
*/