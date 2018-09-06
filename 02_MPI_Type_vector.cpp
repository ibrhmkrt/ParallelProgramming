
#include "mpi.h"
#include <iostream>
using namespace std;

#define SIZE 3
#define TAG 25

int main(int argc, char* argv[])
{
        int myRank,
        size,
            destination;

        double a[SIZE][SIZE] = {{1.0, 2.0, 3.0},
                                {4.0, 5.0, 6.0},
                                {7.0, 8.0, 9.0}};

        double b[SIZE]; //a matrisinin herbir SUTUNU 3 farkli makinede b vektoru icinde depolanacak

        MPI_Status status;
        MPI_Datatype columnType;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Type_vector(SIZE, 1, SIZE, MPI_DOUBLE, &columnType);
        MPI_Type_commit(&columnType);

        if(size == SIZE+1)
        {
                if(myRank == 0)
                {
                        for(int i=0;i<(size-1);i++)
                        {
                                destination=i+1;
                                MPI_Send(&a[0][i], 1, columnType, destination, TAG, MPI_COMM_WORLD);
                        }
                }
                else
                {
                        MPI_Recv(b, SIZE, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status);
                        printf("My Rank = %d  b = %f %f %f\n",myRank,b[0],b[1],b[2]);
                }
        }
        else
                printf("Must specify %d processors. Terminating.\n",SIZE+1);

        MPI_Type_free(&columnType);

        MPI_Finalize();

        return 0;
}

/*
Program Output:

My Rank = 1  b = 1.000000 4.000000 7.000000
My Rank = 2  b = 2.000000 5.000000 8.000000
My Rank = 3  b = 3.000000 6.000000 9.000000

*/
