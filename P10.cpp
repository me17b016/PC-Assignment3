#include<iostream>
#include<string>
#include<time.h>
#include<mpi.h>
using namespace std;

int main(int argc, char** argv) {
	int rank, np;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = stoi(argv[1]);
    int M = stoi(argv[2]);

    int *arr = (int*)malloc(N * sizeof(int));
    srand(time(0));

    cout << "RANK is " << rank << '\n';
    for (int i = 0; i < N; i++) arr[i] = (((rand() + rank) % (rand() + 1))) % (rank + 50), cout << arr[i] << ' ';
    cout << "\n-----------------\n";
  
    int X = 0, NEW_X;
    
    for (int i = 0; i < M; i++) {
        if (rank == X) {
            NEW_X = rand() % np;
            cout << "[ " << X << " => " << NEW_X << " ]" << '\n';
        }
        MPI_Bcast(&NEW_X, 1, MPI_INT, X, MPI_COMM_WORLD);

        if (NEW_X == X) continue;
        if (X == rank) {
            MPI_Send(&arr[0], N, MPI_INT, NEW_X, 1, MPI_COMM_WORLD);
        }
        if (rank == NEW_X) {
            MPI_Recv(&arr[0], N, MPI_INT, X, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        
        X = NEW_X;
    }

    cout << "RANK is " << rank << '\n';
    for (int i = 0; i < N; i++) cout << arr[i] << ' ';
    cout << "\n-----------------\n";

    MPI_Finalize();
}
