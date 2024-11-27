#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Структура для передачи параметров в поток
typedef struct {
    int start;
    int end;
    int mod;
    long long result;
} ThreadData;

// Глобальный мьютекс для синхронизации доступа к результату
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Функция, которую будет выполнять каждый поток
void* factorial_thread(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long result = 1;

    for (int i = data->start; i <= data->end; i++) {
        result = (result * i) % data->mod;
    }

    // Захватываем мьютекс перед записью результата
    pthread_mutex_lock(&mutex);
    data->result = result;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Использование: %s --k <число> --pnum <потоки> --mod <модуль>\n", argv[0]);
        return 1;
    }

    int k, pnum, mod;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--k") == 0) {
            k = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--pnum") == 0) {
            pnum = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--mod") == 0) {
            mod = atoi(argv[++i]);
        }
    }

    if (k < 1 || pnum < 1 || mod < 1) {
        fprintf(stderr, "Ошибка: k, pnum и mod должны быть положительными числами.\n");
        return 1;
    }

    pthread_t threads[pnum];
    ThreadData thread_data[pnum];

    int chunk_size = k / pnum;
    int remainder = k % pnum;

    // Создаем потоки
    for (int i = 0; i < pnum; i++) {
        thread_data[i].start = i * chunk_size + 1;
        thread_data[i].end = (i + 1) * chunk_size;
        if (i == pnum - 1) {
            thread_data[i].end += remainder;
        }
        thread_data[i].mod = mod;
        thread_data[i].result = 1;

        pthread_create(&threads[i], NULL, factorial_thread, &thread_data[i]);
    }

    // Дожидаемся завершения всех потоков
    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    // Объединяем результаты
    long long final_result = 1;
    for (int i = 0; i < pnum; i++) {
        final_result = (final_result * thread_data[i].result) % mod;
    }

    printf("Факториал %d по модулю %d: %lld\n", k, mod, final_result);

    // Освобождаем мьютекс
    pthread_mutex_destroy(&mutex);

    return 0;
}