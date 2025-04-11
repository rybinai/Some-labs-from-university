/*
 * lab6 - 2.c программа для проверки совместного использования позиции файла
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите название исполняемого файла или путь к команде");
        return EXIT_FAILURE;
    }
    // Открываем файл
    int File = open(argv[1], O_RDONLY);
    if (File == -1) {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }
    // Создание копии текущего процесса 
    pid_t pid = fork();
    int s;
    if (pid == -1) {
        perror("Ошибка fork");
        return EXIT_FAILURE;
    }
    // Смещение
    if (pid == 0) {             // 0 - Дочерная программа
        if (lseek(File, 3, SEEK_SET) == -1) {
            perror("Ошибка lseek");
            return EXIT_FAILURE;
        }
    } else {
        // Ожидание завершение процесса
        if (waitpid(pid, &s, 0) != pid) {
            perror("Ошибка waitpid");
            return EXIT_FAILURE;
        } else {
            // if Процесс завершился нормально
            if (WIFEXITED(s)) {
                printf
                    ("Процесс завершился нормально %d\n",
                     WIFEXITED(s));
            }
            // if Процесс завершился сигналом
            if (WIFSIGNALED(s)) {
                printf
                    ("ПРоцесс завершился сигналом %d\n",
                     WIFSIGNALED(s));
            }
        }
        // Проверяем позицию файла после завершения дочернего процесса
        int pos;
        pos = lseek(File, 0, SEEK_CUR);
        printf
            ("Родительский процесс : текущая позиция файла %d\n",
             pos);
    }
    // Закрытие файлов
    if (close(File) == -1) {
        perror("Ошибка при закрытии ");
        return EXIT_FAILURE;
    }
    return 0;
}
