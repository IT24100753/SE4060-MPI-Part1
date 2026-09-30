#include <cstdio>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[30];
    int len;
    MPI_Get_processor_name(name, &len);

    int x[10], y[10];

    if (rank == 1) {
        for (int r = 0; r < 10; r++)
            x[r] = 10 * r;

        printf("Sending message to computer 3 from computer 1\n");
        MPI_Ssend(x, 10, MPI_INT, 3, 0, MPI_COMM_WORLD);
    } else if (rank == 3) {
        MPI_Recv(y, 10, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("in computer 3 the value of y is printed\n");
        for (int r = 0; r < 10; r++)
            printf(" %d ", y[r]);
        printf("\n");
    } else {
        printf("Just a normal process From rank %d machine %s\n", rank, name);
    }

    MPI_Finalize();
    return 0;
}
