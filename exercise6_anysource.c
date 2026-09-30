#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;
    long long niter = 10000000LL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time = MPI_Wtime();

    long long local_niter = niter / size;
    unsigned int seed = time(NULL) + rank * 1000;

    long long count = 0;
    for (long long i = 0; i < local_niter; i++) {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0)
            count++;
    }

    long long total_count = 0;
    if (rank == 0) {
        total_count = count;
        for (int p = 1; p < size; p++) {
            long long temp = 0;
            MPI_Status status;
            MPI_Recv(&temp, 1, MPI_LONG_LONG, MPI_ANY_SOURCE, 10, MPI_COMM_WORLD, &status);
            printf("Rank 0 received %lld from rank %d\n", temp, status.MPI_SOURCE);
            total_count += temp;
        }
    } else {
        MPI_Send(&count, 1, MPI_LONG_LONG, 0, 10, MPI_COMM_WORLD);
    }

    double end_time = MPI_Wtime();

    if (rank == 0) {
        double pi = (double)total_count / niter * 4.0;
        printf("Estimate of pi is %f\n", pi);
        printf("Elapsed Execution Time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
