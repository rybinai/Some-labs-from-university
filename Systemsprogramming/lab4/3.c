/*
 * lab4 - 3.c - утилита readlink
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // путь к файлу
    char buf[PATH_MAX];
    ssize_t size = readlink(argv[1], buf, sizeof(buf));
    if (size == -1) {
        perror("Ошибка вызова функции");
        return EXIT_FAILURE;
    }
    // вывод пути
    buf[size] = '\0';
    printf("%s\n", buf);

    return 0;
}
