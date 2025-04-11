/*
 * lab1.c -- Программа для вывода "Hello world!"
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <string.h>

 // Определение функции main, argc - кол-во аргументов, argv - массив строк
int main(int argc, char *argv[])
{
    // Вывод Hello world
    printf("Hello, world!\n");

    // Вывод кол-во аргументов командой стркои
    printf("Кол-во аргументов: %d\n", argc);

    // Вывод элементов комадной строки
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    
    return 0
}
