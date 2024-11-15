#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Создаем дочерний процесс
    child_pid = fork();

    if (child_pid > 0) {
        // Родительский процесс
        printf("Родительский процесс (PID: %d) создал дочерний процесс (PID: %d)\n", getpid(), child_pid);

        // Родительский процесс не вызывает wait(), чтобы создать зомби-процесс
        sleep(10); // Даем время для проверки зомби-процесса

        // Теперь вызываем wait(), чтобы избавиться от зомби-процесса
        wait(NULL);
        printf("Родительский процесс (PID: %d) завершился\n", getpid());
    } else if (child_pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс (PID: %d) завершается\n", getpid());
        sleep(1); // Добавляем задержку, чтобы родительский процесс успел увидеть зомби-процесс
        exit(0);
    } else {
        // Ошибка при создании процесса
        perror("fork");
        exit(1);
    }

    return 0;
}