#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, value;
    int sum, prod, max, min;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Each process sets its value
    value = rank + 1;

    // Reduce operation: sum values to root process
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Allreduce operations: compute product, max, and min across all processes
    MPI_Allreduce(&value, &prod, 1, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&value, &min, 1, MPI_INT, MPI_MIN, MPI_COMM_WORLD);

    // Only root process prints the result of Reduce
    if (rank == 0) {
        printf("Reduce SUM (only root): %d\n", sum);
    }

    // All processes print the results of Allreduce
    printf("Allreduce PROD (rank %d): %d\n", rank, prod);
    printf("Allreduce MAX  (rank %d): %d\n", rank, max);
    printf("Allreduce MIN  (rank %d): %d\n", rank, min);

    // Finalize MPI environment
    MPI_Finalize();

    return 0;
}
