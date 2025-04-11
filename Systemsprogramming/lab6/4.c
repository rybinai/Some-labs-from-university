/*
 * lab6 - 4.c Аналог функции execlp()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// execlp() - заменяет текущий процесс новым, который будет выполнять указанный исполняемый файл
int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc < 2) {
        perror("Ошибка ввода, введите команды из path");
        return EXIT_FAILURE;
    }
    // Создание копии текущего процесса
    pid_t pid = fork();
    if (pid == -1) {
        perror("Ошибка fork");
        return EXIT_FAILURE;
    }
    // Ожидание pid программы
    if (pid == 0) {             // 0 - Дочерная программа
        // Поиск исполняемого файл
        char *path = getenv("PATH");
        // Разбиение path на отдельные директории
        char *dir = strtok(path, ":");
        while (dir) {
            // Формирование полного пути к файлу
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[1]);
            // Выполнение программы  
            execv(full_path, &argv[1]);
            dir = strtok(NULL, ":");
        }
        perror("Команда не найдена");
        return EXIT_FAILURE;
    } else {
        // Родительский процесс
        int s;
        wait(&s);
        // if Процесс завершился нормально
        if (WIFEXITED(s)) {
            printf
                ("Процесс завершился нормально %d\n",
                 WIFEXITED(s));
        }
        // if Процесс завершился сигналом
        if (WIFSIGNALED(s)) {
            printf
                ("ПРоцесс завершился сигналом %d\n",
                 WIFSIGNALED(s));
        }
    }
    return 0;
}
