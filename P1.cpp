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
	int c = argc;
	if (c < 2 || !stoi(argv[1])) {
		if (!rank) cout << "Please pass the array size\n";
		exit(0);
	}

	int N = stoi(argv[1]);

	if (!rank) {
		int* arr;
		arr = (int*)malloc(N * sizeof(int));
		srand(time(0));
		cout << "Array is : ";
		for (int i = 0; i < N; i++) arr[i] = rand(), cout << arr[i] << ' ';
		cout << '\n';
		int st = 0, en = 0, r = N % np;
		en = (N / np);
		if (r) en++;
		int sum = 0, asum = 0;
		//for (int i = 0; i < N; i++) asum += arr[i];
		for (int i = 0; i < en; i++) sum += arr[i];
		for (int i = 1; i < np; i++) {
			st = en, en += N / np;
			if (r >= i + 1) en++;
			int* tem; tem = (int*)malloc((en - st + 1) * sizeof(int));
			tem[0] = en - st;
			for (int j = st; j < en; j++) tem[j - st + 1] = arr[j];
			MPI_Send(tem, (en - st + 1), MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		for (int i = 1; i < np; i++) {
			int rsum = 0;
			MPI_Recv(&rsum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += rsum;
		}
		cout << "SUM is " << sum << '\n';
	}
	else {
		int n = 1 + N / np;
		int r = N % np;
		if (r && r >= rank + 1) n++;
		int* A; A = (int*)malloc((n) * sizeof(int));
		MPI_Recv(A, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		int sum = 0;
		for (int i = 1; i < n; i++) sum += A[i];
		MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
