
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
        int myRank,      /* rank of a process */
            size,       /* number of processes in MPI_COMM_WORLD */
            collector;  /* process number for the collect data */

        int data,
            *gatheredPtr;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        data=myRank;

        if(myRank==0)//master node
        {
                cout<<"Please give the rank number for the process gathering data : ";

                cin>>collector;//su an collector un kim oldugunu sadece master node biliyor

                cout<<endl;

                if(collector < 0 || collector >= size)
                {
                        cout<<"Error: Invalid rank number ID ("<<collector<<"d) : aborting !...\n";

                        MPI_Abort(MPI_COMM_WORLD,99);
                }
        }

        MPI_Bcast(&collector,1,MPI_INT,0,MPI_COMM_WORLD);//herkes gathering islemini kimin yapacagini bilsin. master broadcast yapiyor.
                                                         //collector un kim oldugunu sadece master node biliyor

        printf("%d sends value of %d as data to the collector\n",myRank,data);

        if(myRank == collector)
                gatheredPtr=new int[size];

        MPI_Gather(&data,1,MPI_INT,gatheredPtr,1,MPI_INT,collector,MPI_COMM_WORLD);

        if(myRank == collector)
        {
                cout<<"ID("<<myRank<<") gathered data [";

                for(int i=0;i<size;i++)
                        cout<<gatheredPtr[i]<<" ";

                cout<<"]\n";

                delete [] gatheredPtr;
        }

        MPI_Finalize();

        return 0;
}
