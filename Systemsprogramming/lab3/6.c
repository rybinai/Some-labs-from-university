/*
 * 6.c - использование dup()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Открытие для чтения
    int File = open(argv[1], O_RDONLY);
    if (File == -1) {
        perror("ОШибка открытия файла");
        return EXIT_FAILURE;
    }
    // Создание дубликата файлового дескриптора 
    int File2 = dup(File);
    if (File2 == -1) {
        perror("Ошибка создания дубликата");
        return EXIT_FAILURE;
    }
    // Перемещение на 1 байт вперед
    int pos = lseek(File, 1, SEEK_CUR);
    if (pos == -1) {
        perror("lseek ошибка");
        return EXIT_FAILURE;
    }
    // Текущая позиция в дубликате 
    int pos2 = lseek(File2, 0, SEEK_CUR);
    if (pos2 == -1) {
        perror("lseek ошибка для дубликата");
        return EXIT_FAILURE;
    }
    // Проверка позиции   в файле
    if (pos == pos2)
        printf("Разделяют\n");
    else
        printf("Не разделяют\n");
    // Закрытие файлов
    if (close(File) == -1 || close(File2) == -1) {
        perror("Ошибка при закрытии");
        return EXIT_FAILURE;
    }
    return 0;
}
