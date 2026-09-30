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

    int x = 30;
    int y;

    if (rank == 1) {
        printf("Sending message to computer 3 from computer 1\n");
        MPI_Ssend(&x, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
    } else if (rank == 3) {
        MPI_Recv(&y, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("in computer 3 the value of y is %d\n", y);
    } else {
        printf("Just a normal process From rank %d machine %s\n", rank, name);
    }

    MPI_Finalize();
    return 0;
}
