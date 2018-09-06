
#include "mpi.h"
#include <iostream>
using namespace std;

#define SIZE 3

int main(int argc, char* argv[])
{
        int myRank,    /* rank of a process */
         size,     /* number of processes in MPI_COMM_WORLD */
         root;     /* process ID for the machine reducing data */

     int *bufferPtr,
         *sumPtr;

     MPI_Init(&argc, &argv);

     MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

     MPI_Comm_size(MPI_COMM_WORLD,&size);

     if(myRank==0)//master node
     {
                 cout<<"Please give the rank number for the process where the data will be reduced to: ";

         cin>>root;//su an root un kim oldugunu sadece master node biliyor

                 cout<<endl;
                 if(root < 0 || root >= size)
         {
                        cout<<"Error: Invalid rank number ID ("<<root<<"d) : aborting !...\n";

                        MPI_Abort(MPI_COMM_WORLD,99);

                        //exit(99);
                }
        }


        MPI_Bcast(&root,1,MPI_INT,0,MPI_COMM_WORLD);//herkes kimin indirgeme yapaagini bilsin. master broadcast yapiyor.
                                                    //root un kim oldugunu sadece master node biliyor

        //MPI_Barrier(MPI_COMM_WORLD);//implicit barrier

        bufferPtr=new int[SIZE];
        for(int i=0;i<SIZE;i++)
                bufferPtr[i]=myRank*i;

        sumPtr=new int[SIZE];
        for(int i=0;i<SIZE;i++)
                sumPtr[i]=0;


        printf("%d's SUM buffer BEFORE Reduce is: %d %d %d\n",myRank,sumPtr[0],sumPtr[1],sumPtr[2]);


        if(myRank == root)
                printf("%d REDUCES an ARRAY with the size of %d\n",myRank,SIZE);

    MPI_Reduce(bufferPtr,sumPtr,SIZE,MPI_INT,MPI_SUM,root,MPI_COMM_WORLD);

    printf("%d's SUM buffer AFTER Reduce is: %d %d %d\n",myRank,sumPtr[0],sumPtr[1],sumPtr[2]);

    MPI_Finalize();

    delete [] bufferPtr;
    delete [] sumPtr;

    return 0;
}



