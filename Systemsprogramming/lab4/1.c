/*
 * lab4 - 1.c - вывод всей информации об указанном объекте
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
    // stat
    struct stat func_stat;
    if (lstat(argv[1], &func_stat) == -1) {
        perror("ОШибка stat");
        return EXIT_FAILURE;
    }
    // вывод типа файла 
    if (S_ISREG(func_stat.st_mode))
        printf("Файл\n");
    else if (S_ISDIR(func_stat.st_mode))
        printf("Каталог\n");
    else if (S_ISCHR(func_stat.st_mode))
        printf("Символьное устройство\n");
    else if (S_ISBLK(func_stat.st_mode))
        printf("Блочное устройство\n");
    else if (S_ISFIFO(func_stat.st_mode))
        printf("Канал\n");
    else if (S_ISLNK(func_stat.st_mode))
        printf("Символическая ссылка\n");
    else if (S_ISSOCK(func_stat.st_mode))
        printf("Сокет\n");
    else
        printf("Неизвестный тип\n");

    // Данные со stat
    printf("тип файла и режим %u\n", func_stat.st_mode);
    printf("номер индексного узла %ld\n",
         func_stat.st_ino);
    printf("номер устройства %ld\n", func_stat.st_dev);
    printf
        ("номер устройства для специальных файлов %ld\n",
         func_stat.st_rdev);
    printf("количество ссылок %ld\n", func_stat.st_nlink);
    printf
        ("идентификатор пользователя владельца %u\n",
         func_stat.st_uid);
    printf
        ("идентификатор группы владельца %u\n",
         func_stat.st_gid);
    printf
        ("размер в байтах, для обычных файлов %ld\n",
         func_stat.st_size);
    printf
        ("время последнего обращения к файлу %llu\n",
         (unsigned long long) func_stat.st_atim.tv_sec);
    printf
        ("время последнего изменения файл %llu\n",
         (unsigned long long) func_stat.st_mtim.tv_sec);
    printf
        ("время последнего изменения состояния файла %llu\n",
         (unsigned long long) func_stat.st_ctim.tv_sec);
    printf
        ("оптимальный размер блока ввода/вывода %ld\n",
         func_stat.st_blksize);
    printf
        ("количество занятых дисковых блоков %ld\n",
         func_stat.st_blocks);

    return 0;
}
