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
	MPI_Request request;
	int N = stoi(argv[1]);
	int* arr = (int*)malloc(N * sizeof(int));
	int* brr = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) arr[i] = rank;
	MPI_Isend(arr, N, MPI_INT, (rank + 1) % np, 0, MPI_COMM_WORLD, &request);
	MPI_Recv(brr, N, MPI_INT, (rank - 1 + np) % np, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	if (!rank) {
		cout << "RANK is " << rank << '\n';
		cout << "PREIVIOS VALUES ";
		for (int i = 0; i < N; i++) cout << arr[i] << ' ';
		cout << '\n';
		cout << "LATEST VALUES ";
		for (int i = 0; i < N; i++) cout << brr[i] << ' ';
		cout << '\n';
		cout << "---------------------\n";

		int *arr_p = (int*)malloc(N * sizeof(int));
		int* brr_p = (int*)malloc(N * sizeof(int));

		for (int i = 1; i < np; i++) {
			MPI_Recv(arr_p, N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(brr_p, N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			cout << "RANK is " << i << '\n';
			cout << "PREIVIOS VALUES ";
			for (int j = 0; j < N; j++) cout << arr_p[j] << ' ';
			cout << '\n';
			cout << "LATEST VALUES ";
			for (int j = 0; j < N; j++) cout << brr_p[j] << ' ';
			cout << '\n';
			cout << "---------------------\n";
		}
	}
	else {
		MPI_Send(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(brr, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
