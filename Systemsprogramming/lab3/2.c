/*
 * 2.c - добавление строки в конец файла 
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 3) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Открытие файла для + строки
    int File = open(argv[1], O_APPEND | O_WRONLY);
    if (File == -1) {
        perror("Файл не доступен");
        return EXIT_FAILURE;
    }
    int _str = strlen(argv[2]);
    // Запись строки
    if (write(File, argv[2], _str) != _str) {
        perror("Ошибка записи строки");
        return EXIT_FAILURE;
    }
    // Закрытие файла
    if (close(File) == -1) {
        perror("Ошибка при закрытии ");
        return EXIT_FAILURE;
    }
    return 0;
}
