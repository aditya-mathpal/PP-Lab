/*
1. Write an MPI program using synchronous send. The sender process sends a word to the receiver. The second process receives the word, toggles each letter of the word and sends it back to the first process. Both processes use synchronous send operations.
*/

#include"mpi.h"
#include<stdio.h>
#include<ctype.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char x[100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    if(rank == 0) {
        fprintf(stdout, "Enter word: ");
        fflush(stdout);
        scanf("%s", x);
        MPI_Ssend(&x, 100, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
        fprintf(stdout, "String \"%s\" sent from process 0\n", x);
        fflush(stdout);
        MPI_Recv(&x, 100, MPI_CHAR, 1, 2, MPI_COMM_WORLD, &status);
        fprintf(stdout, "String \"%s\" received from process 1\n", x);
        fflush(stdout);
    } else {
        MPI_Recv(&x, 100, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);
        fprintf(stdout, "String \"%s\" received from process 0\n", x);
        for(int i = 0; x[i]!=0; i++) {
            if(islower(x[i])) x[i] = toupper(x[i]);
            else x[i] = tolower(x[i]);
        }
        MPI_Ssend(&x, 100, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
        fprintf(stdout, "String \"%s\" sent from process 1\n", x);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}

/*
output:
Enter word: Test
String "Test" received from process 0
String "tEST" sent from process 1
String "Test" sent from process 0
String "tEST" received from process 1
*/