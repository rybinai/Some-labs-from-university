/*
 * lab8 - 1.c программа иллюстрация преобразования порядка байт
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

// Функция для вывода содержимого памяти в формате байтов
void print_memory(const unsigned char *ptr, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        printf("0x%02x", ptr[i]);       // Вывод каждого байта в 16 формате
        if (i < size - 1) {
            printf(":");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите беззнаковое целое 32-битное число");
        return EXIT_FAILURE;
    }
    // Чтение 32-битного числа из командной строки
    uint32_t host = strtoul(argv[1], NULL, 16);

    // Вывод числа в порядке байтов хоста
    printf("host byte order:\n s_addr=0x%08x, ", host); // Вывод заголовка и значения в 16 формате
    print_memory((unsigned char *) &host, sizeof(host));

    // Преобразование числа в сетевой порядок байт
    // htonl — преобразует 32-битное число в сетевой порядок 
    uint32_t network = htonl(host);

    // Вывод числа в сетевом порядке байт
    printf("network byte order:\n s_addr=0x%08x, ", network);   // Весь вывод в одной строке в 16 формате
    print_memory((unsigned char *) &network, sizeof(network));

    // Преобразование числа в строковый формат 
    unsigned char *bytes = (unsigned char *) &network;

    // Формируем строку вручную
    printf("s=%u.%u.%u.%u\n", bytes[0], bytes[1], bytes[2], bytes[3]);

    return 0;
}
