#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
int sum_itog = 0;
pthread_mutex_t mutex;

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
    for (int ind = params->current_number_of_thread; ind < params->mas_len-1; ind += params->number_of_threads){
        if (params->mas1[ind+1] < params->mas1[ind]) {
            sum += 1;
            Sleep(1);
    pthread_mutex_lock(&mutex);
    sum_itog += sum;
    sum = 0;
    pthread_mutex_unlock(&mutex);
        }
    }
}


int main()
{

    clock_t start = clock();
    const int n = 1000; // Размер массива
    const int count_of_threads = 1; // Количество потоков
    int i;
    int mas[n];
    srand(time(0));

    for (i = 0; i < n; i++) {
        mas[i] = rand() % 100;
        //printf("%d ", mas[i]);

    }

    // Массив вывода для каждого потока
    int thread_result[count_of_threads];
    for (i = 0; i < count_of_threads; i++) {
        thread_result[i] = 0;
    };

    // Создание потоков
    pthread_t threads[count_of_threads];
    for (i = 0; i < count_of_threads; i++) {

        struct funcparams *params = malloc(sizeof(struct funcparams));
        params->mas1 = mas;
        params->current_number_of_thread = i;
        params->results = thread_result;
        params->mas_len = n;
        params->number_of_threads = count_of_threads;

        pthread_create(&threads[i], NULL, sum_unordered, params);
    }
    // Ожидание выполнения потоков
    for (i = 0; i < count_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\nNumber of unordered ascending adjacent elements of the vector = %d ", sum_itog);
    printf("\nProgram running time = %.4lf", (float)(clock() - start)/1000);

    return 0;
}