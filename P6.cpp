#include<iostream>
#include<omp.h>
#include<vector>
#include<string>
#include<time.h>
#include<chrono>

using namespace std;

int main(int argc, char** argv) {
  srand(time(0));

  int nthreads = stoi(argv[1]);
  int N = stoi(argv[2]);
  vector<int> arr(N);
  for (int i = 0; i < N; i++) arr[i] = rand();

  int asum = 0;
  for (auto to : arr) asum += to;
  cout << "Ans is " << asum << '\n';

  auto start = chrono::high_resolution_clock::now();

  int total_sum = 0;
  #pragma omp parallel for reduction(+: total_sum) num_threads(nthreads) 
  for (int i = 0; i < N; i++) {
    total_sum += arr[i];
  }
  cout << "Sum is " << total_sum << '\n';
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Time take is " << duration.count() << " ms" << '\n';
  cout << "----------------\n";
}
