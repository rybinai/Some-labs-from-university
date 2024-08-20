/*
         as -ahlsm=task5.lst --32 -gstabs+ -o task5.o task5.S
         ld -melf_i386 -o task5-exe-S task5.o
*/

.include "my-macro"                     # подключение файла с макроопределениями

.bss
        .lcomm buf_vector 10            # для одной возможно получившейся цифры
        .lcomm c,1                      # буфер для чтения текущего символа.

.data                                   # секция данных, распределение памяти

ten:  .long 10
l:      .long 0                         
k:      .long 0
f:      .long 0                         # Поиск строк
i:      .long 0                         # Поиск внутри строки 
sum:  .long 0                           
Matrix:                                 # Матрица, столбцы и строки которой мы будем обрабатывать
        .long  1, 2,  3,  4,  5,  6 
        .long  7, 8,  9,  10, 11, 12
        .long 13, 14, 15, 16, 17, 18
        .long 19, 20, 21, 22, 23, 24 
        .long 25, 26, 27, 28, 29, 30
        .long 31, 32, 33, 34, 35, 36
vector:  .long 0, 0, 0, 0, 0, 0         # вектор получаемый по условию задачи

.text                                   # секция команд процесора

.global _start                          # точка входа - глобальная метка

_start:
        Puts "Введите цифру от 1 до 6 :"                # Ввод номера строки

kdb_input_k:
        Getchar $c                      # Получаем с командной строки значение
        cmpl $0, %eax                   # Конец файл - EOF (введено 0 символов) ?
        je end                          # Да - на завершение программы
        cmpb $'\n', c                   # Это символ перевода строки ?
        je changer
        cmpb $'6', c                    # Код больше кода символа '6' ?
        ja print_err_msg1               # ДА - на вывод сообщения об ошибке
        cmpb $'1', c                    # Код меньше кода символа '1' ?
        jb print_err_msg1               # ДА - на вывод сообщения об ошибке
        movb c, %al                     # Код из с пишем в al
        subl $'0',%eax                  # Получаем число
        movb %al, k                     # Загрузить содержимое al (введенный символ) в байт
        jmp kdb_input_k

changer:        
        cmpl $0, k                      # Было ли введено начальное значение?
        je error_inpit_k                # Нет - жди числа в буфере
        movl k, %eax                    # Копирование элемента k в #eax
        subl $1, %eax                   # Переопределяем точный адрес нужной строчки
        movl %eax, k                    # Копирование элеметна %eax в k
        Puts "Введите цифру от 1 до 6 :"                # Ввод номера столбца

kdb_input_l:
        Getchar $c
        cmpl $0, %eax                   # Конец файл - EOF (введено 0 символов) ?
        je end                          # Да - на завершение программы
        cmpb $'\n', c                   # Это символ перевода строки ?
        je next                         # Нет- вводим следуюший символ
        cmpb $'6', c                    # Код больше кода символа '6' ?
        ja print_err_msg                # ДА - на вывод сообщения об ошибке
        cmpb $'1', c                    # Код меньше кода символа '1' ?
        jb print_err_msg                # ДА - на вывод сообщения об ошибке
        subl %eax, %eax                 # Обнуляем eax
        movb c, %al                     # Код из с пишем в al
        subb $'0',%al                   # Получаем числовое значение символа
        movb %al, l                     # Загрузить содержимое al (введенный символ) в байт
        jmp kdb_input_l

next:
        cmpl $0, l                      # Было ли введено начальное значение?
        je error_inpit_l                # Нет - вывод сообщения об ошибке
        subl %eax,%eax                  # Обнуляем eax
        movl l, %eax                    
        subl $1, %eax                   # Переопределяем точный адрес столбцам
        movl %eax, l
        subl %esi,%esi                  # Установка начального значения цикла по столбцам

pod_k:
        subl %ebx, %ebx                 # j = 0
        movb k, %al                     # Находим номер нужной строки
        movb $24, %cl                   # Умножаем на количество байт в строке
        imul %cl                        # Умножаем al*cl
        mov $Matrix, %edx               # Переносим адрес массива в %edx
        addw %ax, %dx                   # Находим нужную строку, прибавляем к начальному адресу количество байт
        addl %esi, %ebx                 # Переносим в %ebx, значение i

        movl (%edx,%ebx,4), %eax        # Matrix(k,i) = edx + ebx * 4
        movl %eax, sum                  # Переносим

pod_l:
        movl %esi, f                    # Находим нужную строчку для следующего числа
        movb f, %al
        movb $24, %cl                   # Количество байт в строке
        imul %cl                        # Умножаем al*ah
        subl %edx, %edx
        mov $Matrix, %edx
        addw %ax, %dx                   # Находим нужную строчку
        subl %ebx, %ebx                 # Определяем нужный столбец
        addl l, %ebx

        movl  (%edx,%ebx,4), %eax        # Matrix(i,l) = edx + ebx * 4
        addl  %eax, sum                 # Matrix(i,l) + b(i)
        movl sum, %eax
        movl  %esi, i                   # Сохранили значение
        movl %eax, vector(,%esi,4)      # Передает значение из %eax по адресу vector + 4*%esi
        movl $9, %esi 

del1:
        movl  $0, %edx                  # Готовим деление
        idivl ten                       # Делим объединенные регистры edx:eax на 10
        movl %edx, %ebx                 # Переносим остаток от деления в отдельный регистр для получения числового значения (ascii)
        addl $48, %ebx                  # Получаем из цифры код ascii
        movb %bl, buf_vector(%esi)      # Помещаем число в буфер на место соответствующего разряда
        decl  %esi                      # Уменьшаем номер разряда
        cmpl $0, %eax                   # Сравнива/ем частное с нулем
        ja del1                         # НЕТ - продолжаем деление

        movl $4, %eax                   
        movl $1, %ebx
        movl $buf_vector, %ecx          
        movl $10, %edx                  # Длина строки
        int $0x80                       # Прерывание 0x80
        Puts " "
                                        # Продолжаем находить элементы вектора
        subl %esi, %esi
        movl i, %esi                    # Возврат обратно

        incl %esi
        cmpl $6, %esi
        je end
        jmp pod_k

print_err_msg1:
        Puts "Неправильный ввод"
        jmp kdb_input_k

print_err_msg:
        Puts "Неправильный ввод"
        jmp changer

error_inpit_k:
        Puts "Введите k"
        jmp _start

error_inpit_l:
        Puts "Введите l"
        jmp kdb_input_l

text:
        jmp end

end:

Exit $0

.end
