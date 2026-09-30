#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    long long n = 10000000LL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    long long chunk = n / size;
    long long start = rank * chunk + 1;
    long long end = (rank == size - 1) ? n : (start + chunk - 1);

    long long local_sum = 0;
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    long long total_sum = 0;
    if (rank == 0) {
        total_sum = local_sum;
        for (int p = 1; p < size; p++) {
            long long temp = 0;
            MPI_Recv(&temp, 1, MPI_LONG_LONG, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += temp;
        }
    } else {
        MPI_Send(&local_sum, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
    }

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Total Sum: %lld\n", total_sum);
        printf("Elapsed Execution Time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
