#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Параметры для потоковой функции
struct funcparams {
    int* mas1;
    int mas_len;
    int number_of_threads;
    int current_number_of_thread;
    int* results;
};

// Потоковая функция
void *sum_unordered(void* my_params)
{
    // Получение параметров
    struct funcparams* params;
    params = (struct funcparams *) my_params;

    int sum = 0;

    // Подсчет неупорядоченных соседних элементов
    for (int ind = params->current_number_of_thread; ind < params->mas_len; ind += params->number_of_threads){
        if (params->mas1[ind+1] < params->mas1[ind]) {
            sum += 1;
        }
    }
    params->results[params->current_number_of_thread] = sum;
}


int main()
{
    double start = clock();
    const int n = 256*1024; // Размер массива
    const int count_of_threads = 64; // Количество потоков
    int i;
    int mas[n];
    srand(time(0));

    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        //printf("%d ", mas[i]);

    }

    // Массив вывода для каждого потока
    int division[count_of_threads];
    for (i = 0; i < count_of_threads; i++) {
        division[i] = 0;
    };

    // Создание потоков
    pthread_t threads[count_of_threads];
    for (i = 0; i < count_of_threads; i++) {

        struct funcparams *params = malloc(sizeof(struct funcparams));
        params->mas1 = mas;
        params->current_number_of_thread = i;
        params->results = division;
        params->mas_len = n;
        params->number_of_threads = count_of_threads;

        pthread_create(&threads[i], NULL, sum_unordered, params);
    }

    // Ожидание выполнения потоков
    for (i = 0; i < count_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Объединение результатов потоков
    int sum_unordered = 0;
    for (i = 0; i < count_of_threads; i++) {
        sum_unordered += division[i];
    }
    printf("\nNumber of unordered ascending adjacent elements of the vector = %d ", sum_unordered);
    printf("\nProgram running time = %.4lf", (clock() - start) / CLOCKS_PER_SEC);
    return 0;
}