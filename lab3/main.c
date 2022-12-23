/*
To run on replit.com (in Shell):
1. mpicc + mpi.out
2. mpicc main.c
3. mpirun -mca plm_rsh_agent sh -n 4 a.out
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int sum_itog = 0;
int sum = 0;
int main(int argc, char **argv) {
  // size of array
  const int n = 100000;

  int mas[n];
  int i;
  srand(time(0));
  double start, end;

  // define number of processes and ranks of processes
  int procNum, procRank;

  // initialization MPI
  MPI_Init(&argc, &argv);

  // set number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &procNum);

  // set current process
  MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
  if (procRank == 0) {
    for (i = 0; i < n; i++) {
      mas[i] = rand() % 100;
      // printf("%d ", mas[i]);
    }
  } 
  //send mas to another processes
  MPI_Bcast(mas, n, MPI_INT, 0, MPI_COMM_WORLD);
  
  // program start time
  start = MPI_Wtime();
  
  // loop count
  for (int ind = procRank; ind < n - 1; ind += (procNum)) {
      if (mas[ind + 1] < mas[ind]) {
        sum += 1;
        // sleep(0.01);
      }
    }
  printf("Process %d, Result %d\n", procRank, sum);
  
  // waiting for all processes to work
  MPI_Barrier(MPI_COMM_WORLD);

  // aggregation of values of all processes
  MPI_Allreduce(&sum, &sum_itog, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  // program ending time
  end = MPI_Wtime();

  // print results
  if (procRank == argc) {
    printf("\nNumber of unordered ascending adjacent elements of the vector = ""%d",sum_itog);
    printf("\nProgram running time = %.4lf\n", (double)(end - start));
  }

  // terminate MPI
  MPI_Finalize();

  return 0;
}
