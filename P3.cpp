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
	int sum = 0;
	if(rank < N) {
		int start_idx = (N / np) * rank + min(rank, N % np);
		int end_idx = min(N, start_idx + (N / np) + (rank < N % np));
		int* local_arr = (int*)malloc((end_idx - start_idx) * sizeof(int));
		for (int i = start_idx; i < end_idx; i++) local_arr[i - start_idx] = i;
		for (int i = start_idx; i < end_idx; i++) sum += local_arr[i - start_idx];
		if (rank) MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		else {
			for (int i = 1; i < min(np, N); i++) {
				int tem;
				MPI_Recv(&tem, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sum += tem;
			}
			cout << "ACTUAL SUM and MPI SUM " << ((N * (N - 1)) / 2) << ' ' << sum << '\n';
		}
	}
	MPI_Finalize();
}
