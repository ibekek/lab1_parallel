#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int sum_itog = 0;


int main()
{
    const int n = 256*1024; // Размер массива
    const int count_of_threads = 64; // Количество потоков
    const int chunk_size = 64;
    int i;
    int mas[n];
    srand(time(0));
    // создание массива
    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        //printf("%d ", mas[i]);
    }
    clock_t start = clock();

    omp_set_num_threads(count_of_threads); //создание потоков

    // Расчет неупорядоченных значений
    int sum = 0;
    #pragma omp parallel firstprivate(sum)
    {
        #pragma omp for schedule(static, chunk_size) //pragma omp for schedule(dynamic)
        for (int ind = 0; ind < n-1; ind += 1){
            if (mas[ind+1] < mas[ind]) {
                sum += 1;
                //Sleep(1);
            }
        }
        #pragma omp critical
        sum_itog += sum;
    }

    printf("\n\nNumber of unordered ascending adjacent elements of the vector = %d \n", sum_itog);
    printf("\nProgram running time = %.4lf\n", (float)(clock() - start)/1000);

    return 0;
}
