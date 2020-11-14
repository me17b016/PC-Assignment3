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
	int local_sum = 0, global_sum = 0;
	if(rank < N) {
		int start_idx = (N / np) * rank + min(rank, N % np);
		int end_idx = min(N, start_idx + (N / np) + (rank < N % np));
		int* local_arr = (int*)malloc((end_idx - start_idx) * sizeof(int));
		for (int i = start_idx; i < end_idx; i++) local_arr[i - start_idx] = i;
		for (int i = start_idx; i < end_idx; i++) local_sum += local_arr[i - start_idx];		
	}
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (!rank) cout << "ACTUAL SUM and MPI SUM " << ((N * (N - 1)) / 2) << ' ' << global_sum << '\n';
	MPI_Finalize();
}
