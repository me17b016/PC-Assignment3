#include<iostream>
#include<string>
#include<random>
#include<chrono>
#include<mpi.h>
using namespace std;

int main(int argc, char** argv) {
	int rank, np;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int N = stoi(argv[1]);
	int local_scalar = 0, global_scalar = 0;
	if(rank < N) {
		int start_idx = (N / np) * rank + min(rank, N % np);
		int end_idx = min(N, start_idx + (N / np) + (rank < N % np));
		int* local_vector = (int*)malloc((end_idx - start_idx) * sizeof(int));
		srand(time(0));
		for (int i = start_idx; i < end_idx; i++) local_vector[i - start_idx] = (((rand() + rank) % (rand() + 1))) % (rank + 50);
		for (int i = start_idx; i < end_idx; i++) local_scalar += pow(local_vector[i - start_idx], 2);
	}
	MPI_Reduce(&local_scalar, &global_scalar, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (!rank) cout << "SCALAR VALUE is " << global_scalar << '\n';
	MPI_Finalize();
}
