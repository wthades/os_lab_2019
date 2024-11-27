#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Два мьютекса для демонстрации deadlock
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

// Функция, которую будет выполнять первый поток
void* thread1_function(void* arg) {
    // Захватываем первый мьютекс
    pthread_mutex_lock(&mutex1);
    printf("Поток 1 захватил mutex1\n");

    // Имитация работы
    sleep(1);

    // Пытаемся захватить второй мьютекс
    printf("Поток 1 пытается захватить mutex2\n");
    pthread_mutex_lock(&mutex2);
    printf("Поток 1 захватил mutex2\n");

    // Освобождаем оба мьютекса
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

// Функция, которую будет выполнять второй поток
void* thread2_function(void* arg) {
    // Захватываем второй мьютекс
    pthread_mutex_lock(&mutex2);
    printf("Поток 2 захватил mutex2\n");

    // Имитация работы
    sleep(1);

    // Пытаемся захватить первый мьютекс
    printf("Поток 2 пытается захватить mutex1\n");
    pthread_mutex_lock(&mutex1);
    printf("Поток 2 захватил mutex1\n");

    // Освобождаем оба мьютекса
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Создаем потоки
    pthread_create(&thread1, NULL, thread1_function, NULL);
    pthread_create(&thread2, NULL, thread2_function, NULL);

    // Дожидаемся завершения потоков
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Программа завершена.\n");

    return 0;
}