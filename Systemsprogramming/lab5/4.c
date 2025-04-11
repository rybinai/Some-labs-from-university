/*
 * 4.c - Чтение файла посимвольно с использованием fgetc()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Первый аргумент - файл, откуда будем выводить
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    int s;
    // Вывод всех символов с пробелами
    while ((s = fgetc(file)) != EOF) {
        putchar(s);
        putchar(' ');
    }
    // Закрытие файлов
    if (fclose(file) == -1) {
        perror("Ошибка при закрытии ");
        return EXIT_FAILURE;
    }
    return 0;
}
