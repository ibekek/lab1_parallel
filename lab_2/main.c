#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int sum_itog = 0;


int main()
{
    const int n = 256*1024; // ������ �������
    const int count_of_threads = 64; // ���������� �������
    const int chunk_size = 4;
    int i;
    int mas[n];
    srand(time(0));
    double start, end;
    // �������� �������
    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        //printf("%d ", mas[i]);
    }
    start = omp_get_wtime();
    omp_set_num_threads(count_of_threads); //�������� �������

    // ������ ��������������� ��������
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
    end = omp_get_wtime();
    printf("\n\nNumber of unordered ascending adjacent elements of the vector = %d \n", sum_itog);
    printf("\nProgram running time = %.4lf\n", (double)(end - start));

    return 0;
}
