/*
 * lab6 - 1.c программа, запускающая в дочернем процессе другую программу
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

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода, введите название исполняемого файла или путь к команде");
        return EXIT_FAILURE;
    }
    // Создание копии текущего процесса    
    pid_t pid = fork();
    int s;
    if (pid == -1) {
        perror("ОШибка fork");
        return EXIT_FAILURE;
    }
    if (pid == 0) {             // 0 - Дочерная программа
        // execl - Замена текущего процесса - новым
        if (execl(argv[1], argv[1], NULL) == -1) {	
            perror("ОШибка execl");
            return EXIT_FAILURE;
        }
    }
    // waitpid - Ожидание завершения процесса
    if (waitpid(pid, &s, 0) != pid) {
        perror("ОШибка waitpid");
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
    return 0;
}
