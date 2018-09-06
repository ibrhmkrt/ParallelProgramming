
#include "mpi.h"
#include <iostream>
using namespace std;

#define SIZE 3

int main(int argc, char* argv[])
{
        int myRank,   /* rank of a process */
            size;     /* number of processes in MPI_COMM_WORLD */

        int *bufferPtr,
            *sumPtr;

        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

        MPI_Comm_size(MPI_COMM_WORLD,&size);


        bufferPtr=new int[SIZE];
        for(int i=0;i<SIZE;i++)
                bufferPtr[i]=myRank*i;

        sumPtr=new int[SIZE];
        for(int i=0;i<SIZE;i++)
                sumPtr[i]=0;

        printf("%d's SUM buffer BEFORE ALL Reduce is: %d %d %d\n",myRank,sumPtr[0],sumPtr[1],sumPtr[2]);

        MPI_Allreduce(bufferPtr,sumPtr,SIZE,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

        printf("%d's SUM buffer AFTER ALL Reduce is: %d %d %d\n",myRank,sumPtr[0],sumPtr[1],sumPtr[2]);

        MPI_Finalize();

        delete [] bufferPtr;
        delete [] sumPtr;

        return 0;
}