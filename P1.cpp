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
	int local_sum = 0, global_sum = 0;

	if (!rank) {
		int* arr;
		arr = (int*)malloc(N * sizeof(int));
		srand(time(0));
		for (int i = 0; i < N; i++) arr[i] = rand() % 100;
		
		int st = 0, en = 0, r = N % np;
		en = (N / np);
		if (r) en++;

		for (int i = 0; i < en; i++) local_sum += arr[i];
		for (int i = 1; i < np; i++) {
			st = en, en += N / np;
			if (r >= i + 1) en++;
			int* tem; tem = (int*)malloc((en - st + 1) * sizeof(int));
			tem[0] = en - st;
			for (int j = st; j < en; j++) tem[j - st + 1] = arr[j];
			MPI_Send(tem, (en - st + 1), MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		
		MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
		cout << "SUM is " << global_sum << '\n';
	}
	else {
		int n = 1 + N / np;
		int r = N % np;
		if (r && r >= rank + 1) n++;
		int* A; A = (int*)malloc((n) * sizeof(int));
		MPI_Recv(A, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int local_sum = 0;
		for (int i = 1; i < n; i++) local_sum += A[i];
		MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
