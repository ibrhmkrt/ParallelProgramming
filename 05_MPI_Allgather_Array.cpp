
#include "mpi.h"
#include <iostream>
#include <cstdlib> //rand, srand
#include <ctime>   //time(0)
using namespace std;

int main(int argc, char* argv[])
{
        int myRank,     /* rank of a process */
            size,       /* number of processes in MPI_COMM_WORLD */
            printer;    /* process number to print the values */

        int data[2],
            *gatheredPtr;

        srand(time(0));//zamana bagli seed value for random number generator

        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

        MPI_Comm_size(MPI_COMM_WORLD,&size);

        data[0]=myRank;
        data[1]=myRank*myRank;

        if(myRank == 0)//master node
                printer=rand()%size;//bilgiyi ekrana yazdiracak makineyi rastgele sec

        MPI_Bcast(&printer,1,MPI_INT,0,MPI_COMM_WORLD);

        gatheredPtr=new int[2*size];//gonderilecek her bir dizinin boyutu 2 cunku

        printf("%d sends values of data: [%d %d]\n",myRank,data[0],data[1]);

        MPI_Allgather(data,2,MPI_INT,gatheredPtr,2,MPI_INT,MPI_COMM_WORLD);

        if(myRank == printer)
        {
                cout<<"ID("<<myRank<<") gathered data [";
                for(int i=0;i<2*size;i++)
                        cout<<gatheredPtr[i]<<" ";
                cout<<"]\n";
        }

        MPI_Finalize();

        delete [] gatheredPtr;

        return 0;
}

