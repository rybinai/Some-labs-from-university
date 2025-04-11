/*
 * lab8 - 3.c программа для получения имени хоста по IP-адресу (если это возможно)
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите ip-адрес");
        return EXIT_FAILURE;
    }
    struct sockaddr_in sa;      // IPv4
    char host[NI_MAXHOST];      // Буфер для имени хоста

    sa.sin_family = AF_INET;    // IPv4
    if (inet_pton(AF_INET, argv[1], &sa.sin_addr) != 1) {       // Преобразование IP-адреса в бинарный формат
        printf("Ошибка преобразования");
        return EXIT_FAILURE;
    }
    // Получение имени хоста
    int result =
        getnameinfo((struct sockaddr *) &sa, sizeof(sa), host, NI_MAXHOST,
                    NULL, 0, 0);
    if (result != 0) {
        printf("Ошибка получения имени хоста");
        return EXIT_FAILURE;
    }
    // ПРоверка 
    if (strcmp(host, argv[1]) != 0)
        printf
            ("IP-адрес: %s соответствует имени хоста: %s\n",
             argv[1], host);
    else
        printf("IP-адрес: %s не найден\n", argv[1]);

    return 0;
}
