#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int rank, size, num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Please run with at least 2 processes.\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        num = 5;
        printf("Process 0 sends integer: %d\n", num);
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received %d\n", num);
        num = num * 2;
        printf("Process 1 multiplied value = %d\n", num);
    }

    MPI_Finalize();
    return 0;
}
