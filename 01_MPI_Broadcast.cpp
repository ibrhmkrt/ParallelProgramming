
#include "mpi.h"
#include <iostream>
using namespace std;

#define SIZE 5

int main(int argc, char* argv[])
{
     int myRank,    /* rank of a process */
         size,     /* number of processes in MPI_COMM_WORLD */
         root;     /* process ID for the broadcasting machine */

     int *bufferPtr;

     MPI_Init(&argc, &argv);

     MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

     MPI_Comm_size(MPI_COMM_WORLD,&size);

     if(myRank==0)//master node
     {
                cout<<"Please give the rank number for the process broadcasting its own data : ";

                cin>>root;//su an root un kim oldugunu sadece master node biliyor

                cout<<endl;

                if(root<0 || root>=size)
                {
                        cout<<"Error: Invalid rank number ID ("<<root<<"d) : aborting !...\n";

                        MPI_Abort(MPI_COMM_WORLD,99);

                        //exit(99);
                }
      }


      MPI_Bcast(&root,1,MPI_INT,0,MPI_COMM_WORLD);//herkes broadcasti kimin yapacagini bilsin. master broadcast yapiyor.
                                                    //root un kim oldugunu sadece master node biliyor

      //MPI_Barrier(MPI_COMM_WORLD);//implicit barrier


      bufferPtr=new int[SIZE];

      for(int i=0;i<SIZE;i++)
          bufferPtr[i]=myRank*i;

    printf("%d's buffer BEFORE Broadcast is: %d %d %d %d %d\n",myRank,bufferPtr[0],bufferPtr[1],bufferPtr[2],bufferPtr[3],bufferPtr[4]);

    if(myRank == root)
       printf("%d BROADCASTS an ARRAY with the size of %d\n",myRank,SIZE);

    MPI_Bcast(bufferPtr,SIZE,MPI_INT,root,MPI_COMM_WORLD);//root broadcast yapiyor


    printf("%d's buffer After Broadcast is: %d %d %d %d %d\n",myRank,bufferPtr[0],bufferPtr[1],bufferPtr[2],bufferPtr[3],bufferPtr[4]);


    MPI_Finalize();

    delete [] bufferPtr;

    return 0;
}
