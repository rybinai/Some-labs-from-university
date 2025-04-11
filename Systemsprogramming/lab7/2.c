/*
 * lab7 - 2.c функции sigprocmask(), блокировка sigusr1
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Функция обработчик сигнала SIGUSR1
void func_sigusr1(int sig)
{
    if (sig != SIGUSR1) {
        perror
            ("Ошибка SIGUSR1, получен другой сигнал");
        exit(EXIT_FAILURE);
    }
    printf("Сигнал SIGUSR1 обработан\n");
}

int main(int argc, char *argv[])
{
    // Маски, new_mask - блок sigusr1, old_mask - будет хранить маску
    sigset_t new_mask, old_mask;
    // Структура для установки обработчика sigusr1
    struct sigaction sa;
    //  Назначение функции обрабтчика
    sigemptyset(&sa.sa_mask);   // Очистка набора сигналов
    sa.sa_flags = 0;
    sa.sa_handler = func_sigusr1;
    // Проверка установки обработчика
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Ошибка sigusr1");
        return EXIT_FAILURE;
    }
    // Создание пустой маски
    sigemptyset(&new_mask);
    // sigaddset - помещяет сигнал в new_mask
    sigaddset(&new_mask, SIGUSR1);
    // Блокируем сигнал SIGUSR1
    if (sigprocmask(SIG_BLOCK, &new_mask, &old_mask) == -1) {
        perror("Ошибка блокировки сигнала");
        return EXIT_FAILURE;
    }
    printf("Сигнал SIGUSR1 заблокирован\n");

    sleep(5);
    if (raise(SIGUSR1) == -1) {
        perror("Ошибка при отправке сигнала");
    }
    printf("Разблокировка сигнала SIGUSR1\n");
    // Восстановление исходной маски сигналов
    if (sigprocmask(SIG_SETMASK, &old_mask, NULL) == -1) {
        perror
            ("Ошибка восстановления маски сигналов");
        return EXIT_FAILURE;
    }
    printf("Сигнал SIGUSR1 разблокирован\n");
    return 0;
}
