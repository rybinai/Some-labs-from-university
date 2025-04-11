/*
 * lab6 - 3.c - пример использования функции system() 
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
#include <string.h>


int main(int argc, char *argv[])
{
    // Проверка 
    if (argc < 2) {
        perror("Ошибка ввода, введите date");
        return EXIT_FAILURE;
    }
    // Проверка
    if (strcmp(argv[1], "date") != 0) {
        perror("Ошибка ввода, ожидается аргумент date");
        return EXIT_FAILURE;
    }
    // Выполнение команды date
    if (system("date") == -1) {
        printf("ОШибка вызова system");
        return EXIT_FAILURE;
    }
    return 0;
}
