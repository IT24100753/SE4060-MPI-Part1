#include <cstdio>
#include <cstdlib>
#include <mpi.h>

// Exercise 5: Destination (rank 2) doesn't match receiver's expected source (rank 1)
// Causes a deadlock since rank 1 waits for rank 2 to recv, but rank 3 is waiting instead.

int main(int argc, char *argv[])
{
    int rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x = 30, y;

    if (rank == 1) {
        printf("Rank 1 sending to rank 2\n");
        fflush(stdout);
        MPI_Ssend(&x, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
    } else if (rank == 3) {
        printf("Rank 3 waiting for rank 1\n");
        fflush(stdout);
        MPI_Recv(&y, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("Rank 3 received y = %d\n", y);
    }

    MPI_Finalize();
    return 0;
}
