/*
 * 6.c - определения количества символов в строке UTF-8. 
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
    // Установка локали
    setlocale(LC_ALL, "en_US.UTF8");

    // подсчет кол-ва символов
    size_t count = mbstowcs(NULL, argv[1], 0);
    if (count == -1) {
        perror("ОШибка");
        return EXIT_FAILURE;
    }

    printf("Длина строки: %ld\n", count);

    return 0;
}
