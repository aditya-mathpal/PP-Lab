/*
MPI program to find pow(x, rank) for all proceses.
Make even ranked processes print "Hello" and od ones print "World".
*/

#include"mpi.h"
#include<stdio.h>

int power(int x, int rank) {
	int res = 1;
	while(rank) {
		res *= x;
		rank -= 1;
	}
	return res;
}

int main(int argc, char *argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("%d^%d = %d  ",3, rank, power(3, rank));
	if(rank%2 == 0) printf("Hello\n");
	else printf("World\n");

	MPI_Finalize();
	return 0;
}

/*
compile:
mpicc 1.c -o 1.out

run:
mpirun -np 4 1.out

output:
3^2 = 9  Hello
3^3 = 27  World
3^0 = 1  Hello
3^1 = 3  World
*/