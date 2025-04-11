/*
 * lab4 - 5.c - функция ftw()
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// Рекурсивная функция обхода файловой системы
int ftw(const char *base_path)
{
    struct dirent *dir_entry;
    char path[1024];
    DIR *dir = opendir(base_path);
    // Провекра директории
    if (!dir) {
        perror("Не удалось открыть директорию");
        return -1;
    }
    // Чтение содержимого директории
    while ((dir_entry = readdir(dir))) {
        // Пропускаем "." и "..", чтобы не заходить в ту же директорую снова и снова
        if (strcmp(dir_entry->d_name, ".") == 0
            || strcmp(dir_entry->d_name, "..") == 0) {
            continue;
        }
        // Полный путь
        snprintf(path, sizeof(path), "%s/%s", base_path,
                 dir_entry->d_name);
        printf("%s\n", path);

        // Рекурсия, if это директория
        if (dir_entry->d_type == DT_DIR) {
            ftw(path);
        }
    }
    if (closedir(dir) == -1) {
        perror("Ошибка закрытия директории");
        return EXIT_FAILURE;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Проверка аргументов
    if (argc != 2) {
        perror("Ошибка ввода");
        return EXIT_FAILURE;
    }

    ftw(argv[1]);

    return 0;
}
