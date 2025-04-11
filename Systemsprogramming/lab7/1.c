/*
 * lab7 - 1.c используя sigaction() назначить обраотчик сигнала SIGCHILD
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Функция обработки сигнала SIGCHLD
void func_sigchld(int sig)
{
    int s;
    // wnohang - не блокирует родительский процесс, if дочерний ещё не завершился. -1 - ждет завершения дочернего процесса
    pid_t pid;
    // Проверка, что сигнал SIGCHLD
    if (sig != SIGCHLD) {
        perror
            ("ОШибка SIGCHLD, получен другой сигнал");
    }
    // Обработка завершенных процессов
    while ((pid = waitpid(-1, &s, WNOHANG)) > 0) {
        // if Процесс завершился нормально
        if (WIFEXITED(s)) {
            printf
                ("Процесс %d завершился. Код выхода: %d\n",
                 pid, WEXITSTATUS(s));
        }
        // if Процесс завершился сигналом
        if (WIFSIGNALED(s)) {
            printf
                ("Процесс %d завершился сигналом: %d\n",
                 pid, WTERMSIG(s));
        }
    }
}

int main(int argc, char *argv[])
{
    // Структура для настройки обработчика сигнала
    struct sigaction sa;
    // Установка обработчика для sigchld
    sa.sa_handler = func_sigchld;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("Ошибка sigaction");
        return EXIT_FAILURE;
    }
    // Создание нескольких дочерних процессов
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("ОШибка fork");
            return EXIT_FAILURE;
        }
        if (pid == 0) {         // 0 - Дочерная программа
            printf
                ("Дочерний процесс %d начал работу.\n",
                 getpid());
            sleep(2 + i);
            exit(i);
        }
    }
    // Родительский процесс ожидает завершения дочерних процессов
    printf
        ("Ожидание завершения дочерних процессов\n");
    // Ожидание сигналов
    while (1) {
        pause();
    }

    return 0;
}
