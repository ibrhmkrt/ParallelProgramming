#include <mpi.h>
#include <iostream>//cout,cin
#include <cstdlib>//rand,srand
#include <ctime>//time(0)
using namespace std;

int ArrayMaximum(int*,int);//Prototip
void PrintArray(int*,int);//Prototip

#define TAG 25

int main(int argc,char *argv[])
{
        srand((unsigned int)time(0));

        int myRank,
            size,
            diziBoyutu,//Dinamik dizinin boyutu
            kismiBoyut,//Hir islemc payina dusen veri miktari
            globalMaksimum,
            lokalMaksimum;

        int *diziPtr,
            *kismiDiziPtr;

        MPI_Status status;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        if(myRank==0)
        {
                cout<<"Dinamik Dizi Boyutu: ?";
                cin>>diziBoyutu;
                if(diziBoyutu%size!=0)
                {
                        cout<<"Veri Esit Paylastirilamiyor!\n";
                        MPI_Abort(MPI_COMM_WORLD,99);
                }

                diziPtr=new int[diziBoyutu];//yok etmeyi unutma
                for(int i=0;i<diziBoyutu;i++)
                        diziPtr[i]=rand()%2017;

                PrintArray(diziPtr,diziBoyutu);

                kismiBoyut=diziBoyutu/size;

                for(int i=1;i<size;i++)
                        MPI_Send(&kismiBoyut,1,MPI_INT,i,TAG,MPI_COMM_WORLD);

                for(int i=1;i<size;i++)
                        MPI_Send(&diziPtr[i*kismiBoyut],kismiBoyut,MPI_INT,i,TAG,MPI_COMM_WORLD);

                globalMaksimum=ArrayMaximum(diziPtr,kismiBoyut);

                for(int i=1;i<size;i++)
                {
                        MPI_Recv(&lokalMaksimum,1,MPI_INT,i,TAG,MPI_COMM_WORLD,&status);
                        if(lokalMaksimum>globalMaksimum)
                                globalMaksimum=lokalMaksimum;
                }

                cout<<"Dizinin Maksimumu: "<<globalMaksimum<<endl;

                delete [] diziPtr;
        }
        else
        {
                MPI_Recv(&kismiBoyut,1,MPI_INT,0,TAG,MPI_COMM_WORLD,&status);

                kismiDiziPtr=new int[kismiBoyut];//yok etmeyi unutma

                MPI_Recv(kismiDiziPtr,kismiBoyut,MPI_INT,0,TAG,MPI_COMM_WORLD,&status);

                //if(myRank==2)
                        //PrintArray(kismiDiziPtr,kismiBoyut);

                lokalMaksimum=ArrayMaximum(kismiDiziPtr,kismiBoyut);

                MPI_Send(&lokalMaksimum,1,MPI_INT,0,TAG,MPI_COMM_WORLD);

                delete [] kismiDiziPtr;
        }

        MPI_Finalize();
        return 0;
}
