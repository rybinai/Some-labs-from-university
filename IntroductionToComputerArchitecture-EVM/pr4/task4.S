/*
    as -ahlsm=task1.lst --32 -gstabs+ -o task4.o task4.S
    ld -melf_i386 -o task4-exe-S task4.o
*/

.include "my-macro"                 # Подключаем файл с макроопределениями

.data
    delta: .byte 0x30               # Переменная для получения из кода символа ео числовое представление в системе счисления
    summ: .short 0                  # Переменная для хранения суммы 
    number_system: .short 0         # Переменная для номера системе счисления
    count_number: .long 0           # Кол-во возможных цифр в системе счисления
    number_len: .long 0             # Кол-во цифр в числе для вывода
        
.bss
    .lcomm c, 1                     # Буфер для чтения текущего символа
    .lcomm out10, 6                 # Буфер для вывода
    .lcomm n, 1                     # Переменная для обработки текущего символа
    
.text                               # Секция команд процесор

.global _start                      # Точка входа - глобальная метка

_start:

input:
    Puts "Введите цифру"            # макровызов вывода строки в файл stdout (подсказка ввода)

kdb_input:
    Getchar $c                      # макровызов ввода символа со стандартного ввода
    cmpl $0, %eax                   # Конец файл - EOF (введено 0 символов) ?
    je exitprogram                  # Да - вывод суммы
        
    cmpb $'\n', c                   # это символ перевода строки ?
    je plus_numb

    cmpb $'9', c                    # код больше кода символа '9' ?
    ja print_err                    # ДА - на вывод сообщения об ошибке
    cmpb $'0', c                    # код меньше кода символа '0' ?
    jb print_err                    # ДА - на вывод сообщения об ошибке

    movb c, %al                     # Передаем значение из с в n
    movb %al, n

    jmp kdb_input                   # Возвращение в начало 


plus_numb: 
    xorw %ax, %ax                   # Обнуление %ax для правильной обработки

    movb n, %al                     # Присваеваем %al значение n

    subb delta, %al                 # Получаем число из кода
    addw %ax, summ                  # Прибавляем число к сумме
    jo err_buf_over                 # Проверяем на переполнение

    jmp print_summ_numbers_10

print_err: 
    Puts "Это не цифра. Повторите ввод"                   # вывод сообщения об ошибке
    jmp kdb_input                   # на ввод следующего символа

err_buf_over:   
    Puts "Произошло переполнение. Выход."                 # вывод сообщения об переполнении
    jmp exitprogram                 # выход из программы

print_summ_numbers_10: 
    Puts "Сумма введенных чисел в 10 системе счисления "  # вывод сообщения в 10 
    movw $10, number_system  
    movw $5, count_number
    jmp ToString

print_summ_numbers_8:    
    Puts "Сумма введенных чисел в 8 системе счисления "
    movw $8, number_system
    movw $6, count_number
    jmp ToString

print_summ_numbers_2:   
    Puts "Сумма введенных чисел в 2 системе счисления "
    movw $2, number_system
    movw $16, count_number
    jmp ToString

exitprogram: 
    Exit $0                         # выход из программы

ToString:                           # Подготовка чисел для преобразования
        movw number_system, %bx     # Система счисления. На неё будем делить
        movl count_number, %esi     # Адрес самого первого 
        movw summ, %ax              # Копируем номер в %ax
        xorl %edi, %edi             # Обнуляем %edi
        xorl %ecx, %ecx             # Обнуляем %ecx
    
ToStr_begin:                        # Преобразование числа в строку для удобного вывода
    incl %ecx                       # Счетчик длины строки вывода
        movl $0, %edx               # Обнуляем %edx (В нём после операции будет остаток)
        divw %bx                    # Делим %ax на %bx, остаток в %dx
        addb $0x30, %dl             # Прибавляем к %dl 0x30, чтобы перейти к коду числа.
        movb %dl, out10(%esi)       # Копируем содержимое %dl в буфер по нужному смещению

        cmpw $0, %ax                # Дошли до нуля
        je some_changes             # Заканчиваем преобразование и готовим буфер к выводу

        decl %esi                   # Уменьшаем %esi на 1
        jmp ToStr_begin             # Переходим в начало циклa

some_changes: 
    incl count_number               # Прибавляем 1 для сравнения
    movl %ecx, number_len           # Счетчик для длины строки вывода

ToStr_out:                          # Вывод строк на экран
        cmpl count_number, %esi     # В %esi макс. кол-во цифр
        je exitprogram_to_string    # Выходим

        movb out10(%esi), %al       # Копируем байт по адресу  out(%esi) в %al
        movb $0, out10(%esi)        # Записываем 0 по адресу out(%esi)
        movb %al, out10(%edi)       # Записываем значение %al по адресу out(%edi)
        inc %esi                    # Увеличиваем %esi на 1
        inc %edi                    # Увеличиваем %edi на 1
        jmp ToStr_out               # Переходим в начало цикла

exitprogram_to_string:              # Завершение программы и вывода
    movl $4, %eax                   # номер сист. вызова write
    movl $1, %ebx                   # дескриптор стандартного вывода    
    movl $out10, %ecx               # адрес памяти с выводимыми символами
    movl number_len, %edx           # количество байтов для вывода
    int $0x80                       # выполнить системный вызов
    Puts ""
    movw $'',out10                  # обнуляем буфер вывода

    cmpw $10, number_system         # Если 10 была, то идем к 8 
    je print_summ_numbers_8

    cmpw $8, number_system          # Если 8 была, то идем к 2 
    je print_summ_numbers_2
    
    jmp input                       # К вводу следующего числа

.end
