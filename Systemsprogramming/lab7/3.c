/*
 * lab7 - 3.c проверка функции синхронизации родительского и дочернего процессов из листинга 10.17.
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed под MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Устанавливаем обработчик в нулевое значение
static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo)
{                               /* Один обработчик для сигналов SIGUSR1 и SIGUSR2 */
    sigflag = 1;
}

void TELL_WAIT(void)
{
    // Устанавливаем обработчик для сигналов SIGUSR1 и SIGUSR2
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        printf("Ошибка сигнала SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        printf("Ошибка сигнала SIGUSR2");

    // Создаем пустые наборы сигналов
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    // Добавляем SIGUSR1 и SIGUSR2 в новый набор сигналов
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    // Блокировка
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf
            ("Ошибка блокировки сигналов (SIG_BLOCK)");
}

void TELL_PARENT(pid_t pid)
{
    // Сообщение род процессу, что все закончено
    kill(pid, SIGUSR2);
}

void WAIT_PARENT(void)
{
    // Ожидаем сигнал от родительского процесса
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    // Восстановление маски сигналов
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf
            ("Ошибка восстановления маски сигналов (SIG_SETMASK)");
}

void TELL_CHILD(pid_t pid)
{
    // Сообщение доч процессу, что все закончено
    kill(pid, SIGUSR1);
}

void WAIT_CHILD(void)
{
    // Ожидаем сигнал от дочернего процесса
    while (sigflag == 0)
        sigsuspend(&zeromask);
    sigflag = 0;

    // Восстановление маски сигналов
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        printf
            ("Ошибка восстановления маски сигналов (SIG_SETMASK)");
}

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Открытие файла для записи начального значения
    FILE *openFile = fopen(argv[1], "w");
    if (openFile == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    if (fprintf(openFile, "%d", 0) < 0) {
        perror("Ошибка записи в файл");
        return EXIT_FAILURE;
    }
    // Закрытие файла
    if (fclose(openFile) == -1) {
        printf("Ошибка при закрытие файла\n");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    int count = 0;

    TELL_WAIT();
    // Проверка
    if (pid < 0) {
        perror("Ошибка вызова fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) {             // Дочерний процесс
        pid_t parent = getppid();       // Родительский процесс
        WAIT_PARENT();
        while (count < 5) {
            // Открываем для чтения
            openFile = fopen(argv[1], "r");
            if (openFile == NULL) {
                perror
                    ("Ошибка открытия файла в д.процессе");
                return EXIT_FAILURE;
            }
            // ЧИтаем значение из файла
            if (fscanf(openFile, "%d", &count) != 1) {
                perror
                    ("Ошибка чтения файла в д.процессе");
                return EXIT_FAILURE;
            }
            fclose(openFile);
            count++;
            // Открытие для записи
            openFile = fopen(argv[1], "w");
            if (openFile == NULL) {
                perror
                    ("Ошибка открытия файла в д.процессе");
                return EXIT_FAILURE;
            }
            // Запись значения в файл
            if (fprintf(openFile, "%d", count) < 0) {
                perror
                    ("Ошибка запися в файл в д.процессе");
                return EXIT_FAILURE;
            }
            fclose(openFile);
            printf
                ("Дочерний процесс записал в файл: %d\n",
                 count);

            TELL_PARENT(parent);
            WAIT_PARENT();
        }
    } else {                    // Родительский процесс
        pid_t child = pid;
        while (count < 5) {
            // Открываем для чтения
            openFile = fopen(argv[1], "r");
            if (openFile == NULL) {
                perror
                    ("Ошибка открытия файла в р.процессе");
                return EXIT_FAILURE;
            }
            // ЧИтаем значение из файла
            if (fscanf(openFile, "%d", &count) != 1) {
                perror
                    ("Ошибка чтения файла в р.процессе");
                return EXIT_FAILURE;
            }
            fclose(openFile);
            count++;
            // Открытие для записи
            openFile = fopen(argv[1], "w");
            if (openFile == NULL) {
                perror
                    ("Ошибка открытия файла в р.процессе");
                return EXIT_FAILURE;
            }
            // Запись значения в файл
            if (fprintf(openFile, "%d", count) < 0) {
                perror
                    ("Ошибка записи в файл в р.процессе");
                return EXIT_FAILURE;
            }
            fclose(openFile);
            printf
                ("Родительский процесс записал в файл: %d\n",
                 count);

            TELL_CHILD(child);
            WAIT_CHILD();
        }
    }
    return 0;
}
