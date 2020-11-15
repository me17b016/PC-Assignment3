#include<iostream>
#include<math.h>
#include<string>
#include<vector>
#include<time.h>
#include<mpi.h>
#include<thread>
#include <mutex>
using namespace std;
std::mutex mtx;

const int nthreads = 4;
int cnt = 0, sum = 0;

void iittp_barrier(int np, int rank, int tid) {
	if (!tid) {
		int logP = ceil(log(np) / log(2));
		int i = 0;
		int val;
		for (i = 0; i < logP; ++i) {
			int send_to = (rank + (int)pow(2, i)) % np;
			int recv_from = rank - (int)pow(2, i);
			while (recv_from < 0) {
				recv_from += np;
			}
			
			MPI_Send(&i, 1, MPI_INT, send_to, 0, MPI_COMM_WORLD);
			MPI_Recv(&val, 1, MPI_INT, recv_from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	mtx.lock();
	cnt++;
	mtx.unlock();
	while ((cnt % nthreads) != 0);
}

void print(int tid, int rank, int np) {
	iittp_barrier(np, rank, tid);
	for (int i = 0; i < 5; i++) sum++;
	cout << sum << '\n';
}

int main(int argc, char** argv) {
	int rank, np;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	vector<thread> threads;

	for (int tid = 0; tid < nthreads; tid++) {
		threads.push_back(thread(print, tid, rank, np));
	}
	for (auto& th : threads) {
		th.join();
	}
    MPI_Finalize();
}
