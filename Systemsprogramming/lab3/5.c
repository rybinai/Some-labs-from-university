/*
 * 5.c - особенность работы функции read() при чтении из терминала 
 * (возврат из read() происходит при нажатии enter)
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 10
int main(int argc, char *argv[])
{
    char buf_size[BUF_SIZE];
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    int check = read(STDIN_FILENO, buf_size, BUF_SIZE);
    if (check == -1) {
        perror("ОШибка чтения файла");
        return EXIT_FAILURE;
    }

    printf("Байт прочитано: %d\n", check);

    return 0;
}
