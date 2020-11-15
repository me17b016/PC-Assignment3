# PC-Assignment3
Parallel Computing Assignment-3
## Problem 1
Run and Input: `mpiexec -np [number of processes] .\P1.exe [Length of Array N]`

Run and Input: `mpiexec -np 10 .\P1.exe 5`

Output: `SUM is 264`

## Problem 2
Run and Input: `mpiexec -np [number of processes] .\P2.exe [Length of Array N]`

Run and Input: `mpiexec -np 4 .\P2.exe 5`

Output: 
```
RANK is 0
PREIVIOS VALUES 0 0 0 0 0
LATEST VALUES 3 3 3 3 3
--------------------
RANK is 1
PREIVIOS VALUES 1 1 1 1 1
LATEST VALUES 0 0 0 0 0
--------------------
RANK is 2
PREIVIOS VALUES 2 2 2 2 2
LATEST VALUES 1 1 1 1 1
--------------------
RANK is 3
PREIVIOS VALUES 3 3 3 3 3
LATEST VALUES 2 2 2 2 2
--------------------
```
## Problem 3
Run and Input: `mpiexec -np [number of processes] .\P3.exe [Length of Array N]`

Run and Input: `mpiexec -np 4 .\P3.exe 5`

Output: `ACTUAL SUM and MPI SUM 45 45`

## Problem 4
#### Distribution
For Block : `0`

For Cyclic: `1`

For Block-Cyclic: `2`

Run and Input: `mpiexec -np [number of processes] .\P4.exe [Length of Array N] [Distribution]`

Run and Input: `mpiexec -np 4 .\P4.exe 5 1`

Output: `ACTUAL SUM and MPI SUM 45 45`

## Problem 5
Compile: `g++ -std=c++14 P5.cpp`

Run and Input: `a.exe [Number of Threads nthreads] [Length of array N]`

Run and Input: `a.exe 4 100000`

Output: 

```
Sum is 1639203031
Time take is 1995 us
----------------
```
## Problem 6
Compile: `g++ -std=c++14 P6.cpp -o P6 -fopenmp`

Run and Input: `P6.exe [Number of Threads nthreads] [Length of array N]`

Run and Input: `P6.exe 4 100000`

Output: 

```
Sum is 1637062792
Time take is 1824 us
----------------
```
## Problem 7
Run and Input: `mpiexec -np [number of processes] .\P7.exe [Length of Array N]`

Run and Input: `mpiexec -np 4 .\P7.exe 1000`

Output:  `Sum is 49226`

## Problem 8
Run and Input: `mpiexec -np [number of processes] .\P8.exe [Size of Vector N]`

Run and Input: `mpiexec -np 4 .\P8.exe 1000`

Output: `SCALAR VALUE is 844762`

## Problem 9
Compile: `g++ -std=c++14 P9.cpp -o P9 -fopenmp`

Run and Input: `P9.exe [Number of Threads nthreads] [M] [N] [P]`

Run and Input: `P9.exe 2 4 4 4`

Output:
```
MATRIX A:
57 99 3 16
92 91 89 51 
15 68 98 51
45 51 19 49
---------------
MATRIX B:
8 77 65 89
55 83 77 14
24 91 31 43
48 97 6 32
---------------
MATRIX C:
6741 14431 11517 7100
10325 27683 16052 14921 
8660 20664 9555 8133
5973 14180 7735 7104
---------------
Time take is 1029 us
----------------
```
## Problem 10
Run and Input: `mpiexec -np [number of processes] .\P10.exe [Length of Array N] [Number of Iteration M]`

Run and Input: `mpiexec -np 4 .\P10.exe 4 2`

Output: 
```
RANK is 3
7 29 9 12
-----------------
RANK is 3
46 16 33 35
-----------------
RANK is 2
12 4 17 1
-----------------
RANK is 2
12 4 17 1
-----------------
RANK is 1
25 34 25 43
-----------------
RANK is 1
25 34 25 43
-----------------
RANK is 0
46 16 33 35
-----------------
[ 0 => 0 ]
[ 0 => 3 ]
RANK is 0
46 16 33 35
-----------------
```
## Problem 11
Run and Input: `mpiexec -np [number of processes] .\P11.exe`

Run and Input: `mpiexec -np 4 .\P11.exe`

Output: 
```
1 0
1 2
1 1
1 3
22  03

2 1
2 2
33 0
 2
3 3
3 1
0 0
0 2
0 30
 1
 ```
