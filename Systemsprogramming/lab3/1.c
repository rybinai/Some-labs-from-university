/*
 * 1.c - копирование файла
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
    int copyFile = open(argv[1], O_RDONLY);
    if (copyFile == -1) {
        perror
            ("Файл, откуда копировать не доступен");
            return EXIT_FAILURE;
    }
    // Второй аргумент - файл, куда копировать(права - только чтения/записи для владельца)
    int outputFile = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (outputFile == -1) {
        perror
            ("Файл, куда копировать не доступен");
            return EXIT_FAILURE;
    }
    char buf[BUF_SIZE]; 
    int n;
    // запись файлов
    while ((n = read(copyFile, buf, BUF_SIZE)) > 0) {
        if (write(outputFile, buf, n) != n) {
            perror("Ошибка");
        return EXIT_FAILURE;
        }
    }
    // Закрытие файлов
    if (close(copyFile) == -1 || close(outputFile) == -1) {
        perror("Ошибка при закрытии ");
    	return EXIT_FAILURE;
    }
    return 0;
}
