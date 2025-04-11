/*
 * 3.c - поведение функции open()
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
    int File = open(argv[1], O_CREAT | O_EXCL);
    // Проверка open
    if (File == -1) {
        perror("Файл недоступен");
        return EXIT_FAILURE;
    }
    // Закрытие файла
    if (close(File) == -1) {
        perror("Ошибка при закрытии");
        return EXIT_FAILURE;
    }
    return 0;
}
