/*
 * 5.c - МОдификация 4.c, fgetwc()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    setlocale(LC_ALL, "en_US.utf8");    // чтобы работало с utf-8
    // Первый аргумент - файл, откуда будем выводить
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    int s;
    // Вывод всех символов с пробелами
    while ((s = fgetwc(file)) != WEOF) {
        putwchar(s);
        putwchar(' ');
    }
    // Закрытие файлов
    if (fclose(file) == -1) {
        perror("Ошибка при закрытии ");
        return EXIT_FAILURE;
    }
    return 0;
}
