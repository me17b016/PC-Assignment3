#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<chrono>
#include<thread>
using namespace std;

int nthreads = 1;
vector<int> sum_thread;

void compute_sum(int tid, int N, vector<int>& arr) {
  int st = (N / nthreads) * tid;
  int en = (N / nthreads) * (tid + 1);

  for (int i = st; i < en; i++) {
    sum_thread[tid] += arr[i];
  }
}

int main(int argc, char** argv) {
  srand(time(0));    // seed

  nthreads = stoi(argv[1]);
  sum_thread = vector<int>(nthreads);

  int N = stoi(argv[2]); 
  vector<int> arr(N);
  for (int i = 0; i < N; i++) arr[i] = rand();

  if (N < nthreads) {
    for (int i = 0; i < nthreads - N; i++) arr.push_back(0);
    N = nthreads;
  }

  if (nthreads - N % nthreads) {
    for (int i = 0; i < nthreads - N % nthreads; i++) arr.push_back(0);
    N += nthreads - N % nthreads;
  }

  vector<thread> threads;
  auto start = chrono::high_resolution_clock::now();

  for (int i = 0; i < nthreads; i++) {
    threads.push_back(thread(compute_sum, i, N, ref(arr)));
  }

  for (auto &th : threads) th.join();

  int total_sum = 0;
  for (auto to : sum_thread) total_sum += to;
  cout << "Sum is " << total_sum << '\n';

  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Time take is " << duration.count() << " us" << '\n';
  cout << "----------------\n";
}
