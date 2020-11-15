#include<iostream>
#include<string>
#include<random>
#include<chrono>
#include<mpi.h>
using namespace std;

void block_distribution(int& n, int *&local_arr, int N, int rank, int np) {
	if (rank < N) {
		int start_idx = (N / np) * rank + min(rank, N % np);
		int end_idx = min(N, start_idx + (N / np) + (rank < N % np));
		n = end_idx - start_idx;   // Block of size n
		local_arr = (int*)malloc(n * sizeof(int));
		for (int i = start_idx; i < end_idx; i++) local_arr[i - start_idx] = i;
	}
	else {
		n = 1;
		local_arr = (int*)malloc(n * sizeof(int));
		local_arr[0] = 0;
	}
}

void cyclic_distribution(int& n, int*& local_arr, int N, int rank, int np) {
	if (rank < N) {
		n = 0;   // Array of size n
		int p = 0;
		while (p * np + rank < N) n++, p++;
		local_arr = (int*)malloc(n * sizeof(int));
		p = 0;
		for (int i = 0; i < n; i++) local_arr[i] = p * np + rank, p++;
	}
	else {
		n = 1;
		local_arr = (int*)malloc(n * sizeof(int));
		local_arr[0] = 0;
	}
}

void block_cyclic_distribution(int& n, int*& local_arr, int N, int rank, int np) {
	int block_size = 2;
	int blocks = ceil((double)N / block_size);
	int p = 0;
	vector<int> v;
	while (p * np + rank < blocks) {
		int start_idx = (p * np + rank) * block_size;
		int end_idx = min(start_idx + block_size, N);
		n = end_idx - start_idx;
		for (int i = start_idx; i < end_idx; i++) v.push_back(i);
		p++;
	}
	n = v.size();
	if (!n) {
		n = 1;
		local_arr = (int*)malloc(n * sizeof(int));
		local_arr[0] = 0;
	}
	else {
		local_arr = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) local_arr[i] = v[i];
	}
}

int main(int argc, char** argv) {
	int rank, np;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int N = stoi(argv[1]);
	int distribution = stoi(argv[2]);

	int local_sum = 0, global_sum = 0;
	int* local_arr, n;

	if (!distribution) block_distribution(n, local_arr, N, rank, np);
	else if (distribution & 1) cyclic_distribution(n, local_arr, N, rank, np);
	else block_cyclic_distribution(n, local_arr, N, rank, np);

	for (int i = 0; i < n; i++) local_sum += local_arr[i];
	MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (!rank) cout << "ACTUAL SUM and MPI SUM " << ((N * (N - 1)) / 2) << ' ' << global_sum << '\n';
	MPI_Finalize();
}
