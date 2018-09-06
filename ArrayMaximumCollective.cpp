#include <mpi.h>
#include <iostream>//cout,cin
#include <cstdlib>//rand,srand
#include <ctime>//time(0)
using namespace std;

int ArrayMaximum(int*,int);//Prototip
void PrintArray(int*,int);//Prototip

int main(int argc,char *argv[])
{
        srand((unsigned int)time(0));

        int myRank,
            size,
            diziBoyutu,//Dinamik dizinin boyutu
            kismiBoyut,//Hir islemcinin payina dusen veri miktari
            globalMaksimum,
            lokalMaksimum;

        double startTime,endTime,elapsedTime;

        int *diziPtr,
            *kismiDiziPtr;

        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
        MPI_Comm_size(MPI_COMM_WORLD,&size);

        if(myRank==0)
        {
                cout<<"Dinamik Dizi Boyutu:? ";
                cin>>diziBoyutu;

                if(diziBoyutu%size!=0)
                {
                        cout<<"Veri Esit Paylastirilamiyor!\n";
                        MPI_Abort(MPI_COMM_WORLD,99);
                }

                diziPtr=new int[diziBoyutu];//Yok etmeyi unutma
                for(int i=0;i<diziBoyutu;i++)
                        diziPtr[i]=rand()%2017;

                //PrintArray(diziPtr,diziBoyutu);

                kismiBoyut=diziBoyutu/size;

                startTime=MPI_Wtime();//Kronometreyi calistir
        }

        MPI_Bcast(&kismiBoyut,1,MPI_INT,0,MPI_COMM_WORLD);

        kismiDiziPtr=new int[kismiBoyut];//Yok etmeyi unutma

        MPI_Scatter(diziPtr,kismiBoyut,MPI_INT,kismiDiziPtr,kismiBoyut,MPI_INT,0,MPI_COMM_WORLD);

        //printf("Ben %d numarali bilgisayarim. Payima dusen: %d %d\n",myRank,kismiDiziPtr[0],kismiDiziPtr[1]);

        lokalMaksimum=ArrayMaximum(kismiDiziPtr,kismiBoyut);

        MPI_Reduce(&lokalMaksimum,&globalMaksimum,1,MPI_INT,MPI_MAX,0,MPI_COMM_WORLD);

        if(myRank==0)
        {
                endTime=MPI_Wtime();//Kronometreyi durdur
                elapsedTime=endTime-startTime;
                cout<<"Dizinin maksimumu: "<<globalMaksimum<<endl;
                cout<<"Gecen zaman: "<<elapsedTime<<endl;
                delete [] diziPtr;
        }

        delete [] kismiDiziPtr;

        MPI_Finalize();
        return 0;
}

int ArrayMaximum(int *diziPtr,int diziBoyutu)
{
        int maximum=diziPtr[0];
        for(int i=1;i<diziBoyutu;i++)
        {
                if(diziPtr[i]>maximum)
                        maximum=diziPtr[i];
        }
        return maximum;
}

void PrintArray(int *diziPtr,int diziBoyutu)
{
        for(int i=0;i<diziBoyutu;i++)
        {
                cout<<diziPtr[i]<<" ";
        }
        cout<<endl;
}