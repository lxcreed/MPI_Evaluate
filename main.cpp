#include <iostream>
#include <mpi.h>
#include <cmath>
#include <vector>


int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Define the size of the matrix
    int n = 10000; // Change this to your desired size

    // Create the matrix
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    // Sequential computation for the process 0
    if (world_rank == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = i * j; // Replace this with your computation
            }
        }
        std::cout << "Process " << world_rank << " has completed sequential computation." << std::endl;
    }

    // Parallel computation for the other processes
    int start = world_rank * n / world_size;
    int end = (world_rank + 1) * n / world_size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i * j; // Replace this with your computation
        }
    }

    std::cout << "Process " << world_rank << " has completed parallel computation." << std::endl;

    // Gather the results
    if (world_rank != 0) {
        MPI_Send(&matrix[start][0], (end - start) * n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(&matrix[i * n / world_size][0], n * n / world_size, MPI_INT, i, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        }
        std::cout << "Process has gathered the results." << std::endl;
    }

    MPI_Finalize();
    return 0;
}