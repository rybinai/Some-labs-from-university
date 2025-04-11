/*
 * lab8 - 2.c программа для получения всех IP-адресов по имени хоста (если это возможно)
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите имя хоста");
        return EXIT_FAILURE;
    }
    const char *hostname = argv[1];     // Имя хоста из аргументов
    struct addrinfo *res, *p;   // Структура для хранения информации об адресах
    char ip_str[INET6_ADDRSTRLEN];      // Буфер для хранения строкового IP-адреса
    int s;
    // Объявляем структуру для хранения параметров фильтрации результатов
    struct addrinfo hints = {
        .ai_flags = AI_CANONNAME,       // Имя хоста
        .ai_family = AF_UNSPEC, // IPv4,IPv6
        .ai_socktype = SOCK_STREAM,     // Сокет
        .ai_protocol = 0,
        .ai_addrlen = 0,
        .ai_canonname = NULL,
        .ai_addr = NULL,
        .ai_next = NULL
    };
    // Получаем список адресов, связанных с именем хоста
    s = getaddrinfo(hostname, NULL, &hints, &res);
    if (s != 0) {
        printf("Ошибка getaddrinfo");
        return EXIT_FAILURE;
    }
    // Перебираем результаты из списка адресов               
    for (p = res; p != NULL; p = p->ai_next) {
        // Выводим IP-адрес в зависимости от семейства
        void *addr;
        if (p->ai_family == AF_INET) {  // IPv4
            addr = &((struct sockaddr_in *) p->ai_addr)->sin_addr;
            inet_ntop(AF_INET, addr, ip_str, sizeof(ip_str));
            printf("IPv4: %s\n", ip_str);
        } else if (p->ai_family == AF_INET6) {  // IPv6 
            addr = &((struct sockaddr_in6 *) p->ai_addr)->sin6_addr;
            inet_ntop(AF_INET6, addr, ip_str, sizeof(ip_str));
            printf("IPv6: %s\n", ip_str);
        } else {
            printf("Неизвестный тип адреса\n");
        }
    }
    // Освобождаем память, выделенную для списка адресов
    freeaddrinfo(res);

    return 0;
}
