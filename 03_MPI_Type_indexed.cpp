
#include "mpi.h"
#include <iostream>
using namespace std;

#define SIZE 4
#define NUMBER_OF_ELEMENTS 10
#define TAG 25

int main(int argc,char* argv[])
{
        int myRank,
        size;

        double a[SIZE][SIZE] = {{1.0, 2.0, 3.0, 4.0},
                                {5.0, 6.0, 7.0, 8.0},
                                {9.0, 10.0, 11.0, 12.0},
                                {13.0, 14.0, 15.0, 16.0}};

        double b[NUMBER_OF_ELEMENTS];//a matrisinin ust yarim ucgenindeki 10 eleman bu b dizisi icinde depolanacak

        int count,
            blocklengths[4],
            indices[4];

        count = 4;

        blocklengths[0] = 4;
        blocklengths[1] = 3;
        blocklengths[2] = 2;
        blocklengths[3] = 1;

        indices[0] = 0;
        indices[1] = 5;
        indices[2] = 10;
        indices[3] = 15;

        MPI_Status status;
        MPI_Datatype indexType;

        MPI_Init(&argc,&argv);
       MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Type_indexed(count, blocklengths, indices, MPI_DOUBLE, &indexType);
        MPI_Type_commit(&indexType);

        if(myRank == 0)
        {
                for(int i=1;i<size;i++)
                        MPI_Send(a, 1, indexType, i, TAG, MPI_COMM_WORLD);
        }
        else
        {
                MPI_Recv(b, NUMBER_OF_ELEMENTS, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, &status);
        printf("My Rank = %d  b = %f %f %f %f %f %f %f %f %f %f \n"
                            ,myRank, b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7], b[8], b[9]);
        }

        MPI_Type_free(&indexType);
        MPI_Finalize();

        return 0;
}

/*
Program Output:

My Rank = 1  b = 1.000000 2.000000 3.000000 4.000000 6.000000 7.000000 8.000000 11.000000 12.000000 16.000000
My Rank = 3  b = 1.000000 2.000000 3.000000 4.000000 6.000000 7.000000 8.000000 11.000000 12.000000 16.000000
My Rank = 2  b = 1.000000 2.000000 3.000000 4.000000 6.000000 7.000000 8.000000 11.000000 12.000000 16.000000

*/

