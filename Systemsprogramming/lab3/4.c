/*
 * 4.c - lseek(), read()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }
    // Открыти файла для перезаписи
    int File = open(argv[1], O_RDWR | O_APPEND);
    if (File == -1) {
        perror("Ошибка при открытии файла");
        return EXIT_FAILURE;
    }
    // Проверка lseek в начале файла
    int check = lseek(File, 0, SEEK_CUR);
    if (check == -1) {
        perror("lseek ошибка");
        return EXIT_FAILURE;
    }
    // Смещяемся от начала файла на 3 байта
    int newpos = lseek(File, 3, SEEK_SET);
    if (newpos == -1) {
        perror
            ("lseek ошибка - не удалось переместить указатель");
        return EXIT_FAILURE;
    }
    // ЧТение данных из буффера
    char buf_size[BUF_SIZE];
    int text = read(File, buf_size, BUF_SIZE);
    if (text == -1) {
        perror
            ("read ошибка - ошибка при чтении файла");
        return EXIT_FAILURE;
    }
    // Запись в файл
    if (write(File, buf_size, BUF_SIZE) != BUF_SIZE) {
        perror("Ошибка в закрытии файла");
        return EXIT_FAILURE;
    }
    // Закрытие файла
    if (close(File) == -1) {
        perror("Ошибка при закрытии");
        return EXIT_FAILURE;
    }
    return 0;
}
