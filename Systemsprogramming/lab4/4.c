/*
 * lab4 - 4.c - утилита chmod
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 3) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Чтение и проверка прав доступа 
    char *endptr;
    int mode = strtol(argv[1], &endptr, 8);
    // Проверка на ошибки при преобразовании
    if (*endptr != '\0' || mode < 0 || mode > 0777) {
        perror("Ошибка ввода прав доступа");
        return EXIT_FAILURE;
    }
    // Изменение прав доступа с помощью chmod
    if (chmod(argv[2], mode) == -1) {
        perror("Ошибка изменения прав доступа");
        return EXIT_FAILURE;
    }
    printf
        ("Права доступа к файлу %s успешно изменены на %o\n",
         argv[2], mode);

    return 0;
}
