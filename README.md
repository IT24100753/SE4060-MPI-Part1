# SE4060 Parallel Computing - Lab Sheet: MPI Part 1

## Overview
This repository contains solutions for the SE4060 Parallel Computing Lab (MPI Part 1).

## Exercises

### Exercise 1: Hello World (`HelloMPI.c`)
Basic MPI program to initialize the environment, query the rank and processor name, and print from root and worker processes.
- **Compile**: `mpicc -o HelloMPI HelloMPI.c`
- **Run**: `mpirun -n 2 ./HelloMPI`

### Exercise 2: Parallel Sum (`exercise2_sum.c`)
Parallel summation of numbers from 1 to 10,000,000 across multiple nodes using MPI. Uses 64-bit integers to prevent overflow.
- **Compile**: `mpicc -o exercise2_sum exercise2_sum.c`
- **Run**: `mpirun -n 4 ./exercise2_sum`

### Exercise 3: Monte Carlo Pi (`exercise3_pi.c`)
Calculates Pi using the Monte Carlo method for 10,000,000 iterations. Each process generates random points independently using `rand_r` and sends its count to rank 0.
- **Compile**: `mpicc -o exercise3_pi exercise3_pi.c`
- **Run**: `mpirun -n 4 ./exercise3_pi`

### Exercise 4: Graphs & Speedup (`benchmark_and_plot.py`)
Benchmarks execution time and speedup across 1, 2, 4, and 8 processors for Exercises 2 and 3, saving graphs as PNGs.
- **Run**: `python3 benchmark_and_plot.py`
- **Outputs**: `time_vs_processors.png`, `speedup_vs_processors.png`, `benchmark_results.csv`

### Exercise 5: Communication Mismatch & Buffered Send
1. **Source / Destination Mismatch** (`exercise5_mismatch.cc`): Rank 1 sends to rank 2 with `MPI_Ssend`, while rank 3 waits for rank 1. Result: Deadlock.
2. **Buffered Send** (`exercise5_bsend.cc`): Rewrites `message2.cc` using `MPI_Bsend` with an attached buffer without replacing the original payload variables `x` and `y`.

### Exercise 6: MPI_ANY_SOURCE (`exercise6_anysource.c`)
Rewrites Exercise 3 so rank 0 receives using `MPI_ANY_SOURCE`. Messages are collected dynamically on a first-come, first-served basis, avoiding head-of-line blocking.

### Exercise 7: BSend + MPI_ANY_SOURCE (`exercise7_bsend.c`)
Rewrites Exercise 6 using `MPI_Bsend` on worker ranks and `MPI_ANY_SOURCE` on rank 0.

## Baseline Code
- `messages1.cc`: Sends an integer from rank 1 to rank 3 using `MPI_Ssend`.
- `messaage2.cc` / `messages2.cc`: Sends an array of 10 integers from rank 1 to rank 3 using `MPI_Ssend`.

## How to Build & Test

```bash
# Build all exercises
make all

# Run full test suite
bash run_tests.sh

# Clean build files
make clean
```

## Batch Job Submission
- **PBS**: `qsub job1.pbs` (2 processes) or `qsub job_messages.pbs` (4 processes)
- **Slurm (Archer2)**: `sbatch job_mpi_archer.job`
