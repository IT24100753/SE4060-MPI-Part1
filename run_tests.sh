#!/bin/bash
set -e

echo "Compiling all programs..."
make clean
make all

echo "--- Testing Exercise 1 (HelloMPI) ---"
mpirun -n 2 ./HelloMPI

echo "--- Testing Baseline Messages ---"
mpirun -n 4 ./messages1
mpirun -n 4 ./messages2

echo "--- Testing Exercise 2 (Parallel Sum) ---"
mpirun -n 4 ./exercise2_sum

echo "--- Testing Exercise 3 (Monte Carlo Pi) ---"
mpirun -n 4 ./exercise3_pi

echo "--- Testing Exercise 5 Part 1 (Mismatch Deadlock) ---"
if timeout 3s mpirun -n 4 ./exercise5_mismatch > /dev/null 2>&1; then
    echo "Warning: did not deadlock"
else
    echo "Deadlock confirmed as expected."
fi

echo "--- Testing Exercise 5 Part 2 (Bsend) ---"
mpirun -n 4 ./exercise5_bsend

echo "--- Testing Exercise 6 (MPI_ANY_SOURCE) ---"
mpirun -n 4 ./exercise6_anysource

echo "--- Testing Exercise 7 (Bsend + ANY_SOURCE) ---"
mpirun -n 4 ./exercise7_bsend

echo "--- Running Benchmarks and Plotting ---"
python3 benchmark_and_plot.py

echo "Done! All tests completed."
