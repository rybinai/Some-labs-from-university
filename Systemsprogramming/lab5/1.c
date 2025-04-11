/*
 * lab5 - 1.c - аналог программы 3.1 (копирование файла) с использованием потоковых фунций fopen(), fread(), fwrite(), fclose().
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

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 3) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Первый аргумент - файл, откуда копировать
    FILE *copyFile = fopen(argv[1], "r");
    if (copyFile == NULL) {
        perror
            ("Ошибка открытия входного файла");
        return EXIT_FAILURE;
    }
    // Второй аргумент - файл, куда копировать
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror
            ("Ошибка открытия выходного файла");
        return EXIT_FAILURE;
    }
    char buf[BUF_SIZE];
    int n;
    // Копирование данных
    while ((n = fread(buf, 1, BUF_SIZE, copyFile)) > 0) {
        if (fwrite(buf, 1, n, outputFile) != n) {
            perror("Ошибка записи в файл");
            return EXIT_FAILURE;
        }
    }
    // Закрытие файлов
    if (fclose(copyFile) == -1 || fclose(outputFile) == -1) {
        perror("Ошибка при закрытии ");
        return EXIT_FAILURE;
    }
    return 0;
}
