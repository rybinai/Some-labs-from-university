/*
 * lab5 - 2.c - Измерьте время работы 1.c
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
#include <sys/time.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 3) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Получение размера блока с помощью stat
    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1) {
        perror
            ("Ошибка получения информации о файле");
        return EXIT_FAILURE;
    }
    // Блоки по 1 байт, 1 килобайт, 1 мб и st_blksize
    size_t block_sizes[] = { 1, 1024, 1024 * 1024, file_stat.st_blksize };
    // Определение кол-во элементов в block_sizes
    size_t num_sizes = sizeof(block_sizes) / sizeof(block_sizes[0]);
    // Цикл по буферам
    for (size_t i = 0; i < num_sizes; i++) {
        size_t buffer_size = block_sizes[i];

        // Открытие файлов для копирования
        FILE *copyFile = fopen(argv[1], "r");
        if (copyFile == NULL) {
            perror
                ("Ошибка открытия входного файла");
            return EXIT_FAILURE;
        }

        FILE *outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            perror
                ("Ошибка открытия выходного файла");
            return EXIT_FAILURE;
        }

        char *buf = malloc(buffer_size);
        if (buf == NULL) {
            perror("Ошибка выделения памяти");
            return EXIT_FAILURE;
        }
        // Переменные начала и конца времени
        struct timeval start, end;

        // Старт
        gettimeofday(&start, NULL);

        size_t n;
        while ((n = fread(buf, 1, buffer_size, copyFile)) > 0) {
            if (fwrite(buf, 1, n, outputFile) != n) {
                perror("Ошибка записи в файл");
                return EXIT_FAILURE;
            }
        }

        // Освобождение буфера и закрытие файлов
        free(buf);
        if (fclose(copyFile) == -1 || fclose(outputFile) == -1) {
            perror("Ошибка при закрытии ");
            return EXIT_FAILURE;
        }
        // Конец
        gettimeofday(&end, NULL);

        // Вычисление времени
        long seconds = end.tv_sec - start.tv_sec;
        long micros = end.tv_usec - start.tv_usec;
        long elapsed = seconds * 1000000 + micros;      // в микросекунды
        printf
            ("Время выполнения при размере буфера %zu байт: %ld микросекунд\n",
             buffer_size, elapsed);
    }

    return 0;
}
