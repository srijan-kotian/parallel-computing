#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int data[4] = {10, 20, 30, 40};
    int recv;

    // Initialize MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank and size
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Scatter one element of data to each process
    MPI_Scatter(data, 1, MPI_INT, &recv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process increments its received value
    recv += 1;

    // Gather the modified values back to the root process
    MPI_Gather(&recv, 1, MPI_INT, data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Root process prints the gathered data
    if (rank == 0) {
        printf("Gathered data: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    // Finalize MPI environment
    MPI_Finalize();
    return 0;
}
