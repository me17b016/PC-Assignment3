# PC-Assignment3
Parallel Computing Assignment-3
## Problem 1
Compile: `mpiexec -np [number of processes] .\P1.exe [Length of Array N]`

Compile and Input: `mpiexec -np 10 .\P1.exe 5`

Output: `SUM is 264`

## Problem 2
Compile: `mpiexec -np [number of processes] .\P1.exe [Length of Array N]`

Compile and Input: `mpiexec -np 4 .\P1.exe 5`

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
