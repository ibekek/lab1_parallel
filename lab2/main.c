#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int sum_itog = 0;
double prog_time;

int main()
{
    const int n = 1000; // array size
    const int count_of_threads = 1; // threads num
    const int chunk_size = 4;
    int i;
    int mas[n];
    srand(time(0));
    double start, end;
    // filling array
    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        //printf("%d ", mas[i]);
    }
    double omp_get_wtime();
    omp_set_num_threads(count_of_threads); //creating threads

    // count loop
    int sum = 0;
    #pragma omp parallel firstprivate(sum)
    {
        #pragma omp for schedule(static, chunk_size) //pragma omp for schedule(dynamic)
        for (int ind = 0; ind < n-1; ind ++){
            if (mas[ind+1] < mas[ind]) {
                sum += 1;
                //Sleep(1);
            }
        }
        #pragma omp critical
        sum_itog += sum;
    }
    double a = omp_get_wtime();
    prog_time - omp_get_wtick();
    printf("\n\nNumber of unordered ascending adjacent elements of the vector = %d \n", sum_itog);
    printf("\nProgram running time = %.4lf\n", prog_time);

    return 0;
}
