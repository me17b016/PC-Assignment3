#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<chrono>
#include<thread>
using namespace std;

int nthreads = 1;
int m = 1, n = 1, p = 1;

int main(int argc, char** argv) {
  srand(time(0));
  
  if (argc >= 5) {
    nthreads = stoi(argv[1]);
    m = stoi(argv[2]), n = stoi(argv[3]), p = stoi(argv[4]);
  }

  int* arr = (int*)malloc((m * n) * sizeof(int));
  int* brr = (int*)malloc((n * p) * sizeof(int));
  int* crr = (int*)malloc((m * p) * sizeof(int));
  int* c = (int*)malloc((m * p) * sizeof(int));
  for (int i = 0; i < m * n; i++) arr[i] = rand() % 100;
  for (int i = 0; i < n * p; i++) brr[i] = rand() % 100;
  auto start = chrono::high_resolution_clock::now();
  
  #pragma omp parallel for collapse(2) schedule(static) num_threads(nthreads)
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      int tem = 0;
      for (int k = 0; k < n; k++) {
        tem += arr[i * n + k] * brr[j + k * p];
      }
      crr[i * p + j] = tem;
    }
  } 
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

  cout << "MATRIX A:\n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) cout << arr[i * n + j] << ' ';
    cout << '\n';
  }
  cout << "---------------\nMATRIX B:\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) cout << brr[i * p + j] << ' ';
    cout << '\n';
  }
  cout << "---------------\nMATRIX C:\n";
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) cout << crr[i * p + j] << ' ';
    cout << '\n';
  }

  cout << "---------------\nTime take is " << duration.count() << " us" << '\n';
  cout << "----------------\n";
}
