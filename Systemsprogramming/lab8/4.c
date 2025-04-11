/*
 * lab8 - 4.c TCP эхо-сервер
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>

#define MAX_BUFFER 1024

// Очистка зомби процессов
void killl(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0) {
        // Очистка завершившихся процессов
    }
}

void check_signal(void (*result)(int), const char *msg) {
    if (result == SIG_ERR) {
        perror(msg);
        exit(EXIT_FAILURE);  
    }
}

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите номер порта без лишних элементов");
        return EXIT_FAILURE;
    }
    int port = atoi(argv[1]);   // Получаем номер порта, atoi - str -> int
    if (port <= 0 || port > 65535) {
        printf("Некорректный номер порта");
        return EXIT_FAILURE;
    }
    // СОздание сокета
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[MAX_BUFFER];
    char *host_inet_ntoa;
    ssize_t back;
    // Создаем TCP-сокет
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Ошибка создания сокета");
        return EXIT_FAILURE;
    }
    // Настройка адреса сервера
    server_addr.sin_family = AF_INET;   // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Разрешение серверу принимать все соединения
    server_addr.sin_port = htons(port); // Порт => сетевой порядок байтов

    // Привязываем сокет к адресу
    if (bind
        (server_socket, (struct sockaddr *) &server_addr,
         sizeof(server_addr)) == -1) {
        perror("Ошибка привязки сокета");
        return EXIT_FAILURE;
    }
    // Прослушиване порта
    if (listen(server_socket, 5) == -1) {
        perror("Ошибка прослушивания порта");
        return EXIT_FAILURE;
    }
    printf("Сервер слушает на порту %d\n", port);

    // Зомби
    check_signal(signal(SIGCHLD, killl), "Ошибка установки обработчика SIGCHLD");

    while (1) {
        // Принимаем новое соединение
        client_socket =
            accept(server_socket, (struct sockaddr *) &client_addr,
                   &client_addr_len);
        if (client_socket == -1) {
            perror
                ("Ошибка при принятии соединения");
            return EXIT_FAILURE;
        }
        // Вывод информации о клиенте
        // inet_ntoa - ip adrec => str
        if ((host_inet_ntoa = inet_ntoa(client_addr.sin_addr)) == NULL) {
            printf("Ошибка преобразования ip адреса в строку");
            return EXIT_FAILURE;
        }
        printf("Соединение от %s:%d\n",
               host_inet_ntoa,
               ntohs(client_addr.sin_port));

        // Создание дочернего процесса для клиента
        pid_t pid = fork();
        if (pid == -1) {
            perror
                ("Ошибка при создании дочернего процесса");
            close(client_socket);
            return EXIT_FAILURE;
        }
        if (pid == 0) {         // Дочерний процесс
            if (close(server_socket) == -1) { // Закрываем серверный сокет в дочернем процессе
            	perror("Ошибка закрытия server_socket");
            	return EXIT_FAILURE;
            }
            // Чтение и отправка данных обратно
            while ((back =
                    recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
                // Отправка полученных данных обратно
                if (send(client_socket, buffer, back, 0) == -1) {
                   perror("Ошибка при отправке данных");
                   return EXIT_FAILURE;
                }
            }
            if (back == 0) {
                printf
                    ("Соединение закрыто клиентом\n");
            } else if (back == -1) {
                perror
                    ("Ошибка при получении данных");
            }
            // Закрытие сокет клиента
            if (close(client_socket) == -1) {
            	perror("Ошибка закрытия client_socket");
            	return EXIT_FAILURE;
            }
            exit(0);
        } else {                // Родительский процесс
            if (close(client_socket) == -1) {
            	perror("Ошибка закрытия client_socket");
            	return EXIT_FAILURE;
            }
        }
    }
    return 0;
}
