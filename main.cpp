#include <iostream>
#include <mpi.h>
#include <cmath>
#include <vector>
#include <string>


int main(int argc, char **argv) {
    int n_scale = std::stoi(argv[1]);

    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Define the size of the matrix
    int n = 10 * n_scale;

    // Create the matrix
    static std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

    // for time measure
    double start_time = MPI_Wtime();

    // Parallel computation, if world_size == 1, is a sequential computation
    int start = world_rank * n / world_size;
    int end = (world_rank + 1) * n / world_size;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = i * j; // Replace this with your computation
        }
    }

    // std::cout << "Process " << world_rank << " has completed parallel computation." << std::endl;

    // Gather the results
    if (world_rank != 0) {
        MPI_Send(&matrix[start][0], (end - start) * n, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < world_size; i++) {
            MPI_Recv(&matrix[i * n / world_size][0], n * n / world_size, MPI_INT, i, 0, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
        }
        // for time measure
        double end_time = MPI_Wtime();
        double time_cost = end_time - start_time;

        std::cout << "Process " << world_rank << " has gathered the results: ";
        std::cout << world_size << " parallel processes, " << "n " << n_scale << ", time cost " << time_cost * 1000
                  << "ms"
                  << std::endl;
    }

    MPI_Finalize();
    return 0;
}