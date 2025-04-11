/*
 * lab4 - 2.c - утилита du
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    int totalsize = 0;
    struct stat func_stat;
    // Вывод размеров каждого файла 
    for (int i = 1; i < argc; i++) {
        if (stat(argv[i], &func_stat) == -1) {
            perror
                ("ОШибка получения данных о файле\n");
            return EXIT_FAILURE;
        }
        totalsize += func_stat.st_blocks / 2;
    }

    // общий размер всех файлов
    printf("Общий размер всех файлов %d\n",
           totalsize);

    return 0;
}
