/*
 * lab2.c -- 2lab
 *
 * Copyright (c) <2024>, Rybin Alexey.
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

int main()
{
    // значение всех пределов ISO C (2.6)
    printf("1) Значения всех пределов ISO C\n");
    printf("CHAR_BI = %d\n", CHAR_BIT);
    printf("CHAR_MAX = %d\n", CHAR_MAX);
    printf("CHAR_MIN = %d\n", CHAR_MIN);
    printf("SCHAR_MAX = %d\n", SCHAR_MAX);
    printf("SCHAR_MIN = %d\n", SCHAR_MIN);
    printf("UCHAR_MAX = %d\n", UCHAR_MAX);
    printf("INT_MAX = %d\n", INT_MAX);
    printf("INT_MIN = %d\n", INT_MIN);
    printf("UINT_MAX = %u\n", UINT_MAX);
    printf("SHRT_MAX = %d\n", SHRT_MAX);
    printf("SHRT_MIN = %d\n", SHRT_MIN);
    printf("USHRT_MAX = %d\n", USHRT_MAX);
    printf("LONG_MAX = %ld\n", LONG_MAX);
    printf("LONG_MIN =  %ld\n", LONG_MIN);
    printf("ULONG_MAX = %lu\n", ULONG_MAX);
    printf("LLONG_MAX = %lld\n", LLONG_MAX);
    printf("LLONG_MIN = %lld\n", LLONG_MIN);
    printf("ULLONG_MAX = %llu\n", ULLONG_MAX);
    printf("MB_LEN_MAX = %d\n", MB_LEN_MAX);

    // значения всех пределов POSIX(2.8), (2.9)
    printf("2) Значения всех пределов POSIX (2.8)\n");
    printf("_POSIX_ARG_MAX = %d\n", _POSIX_ARG_MAX);
    printf("_POSIX_CHILD_MAX = %d\n", _POSIX_CHILD_MAX);
    printf("_POSIX_HOST_NAME_MAX = %d\n", _POSIX_HOST_NAME_MAX);
    printf("_POSIX_LINK_MAX = %d\n", _POSIX_LINK_MAX);
    printf("_POSIX_LOGIN_NAME_MAX = %d\n", _POSIX_LOGIN_NAME_MAX);
    printf("_POSIX_MAX_CANON = %d\n", _POSIX_MAX_CANON);
    printf("_POSIX_MAX_INPUT = %d\n", _POSIX_MAX_INPUT);
    printf("_POSIX_NAME_MAX = %d\n", _POSIX_NAME_MAX);
    printf("_POSIX_NGROUPS_MAX = %d\n", _POSIX_NGROUPS_MAX);
    printf("_POSIX_OPEN_MAX = %d\n", _POSIX_OPEN_MAX);
    printf("_POSIX_PATH_MAX = %d\n", _POSIX_PATH_MAX);
    printf("_POSIX_PIPE_BUF = %d\n", _POSIX_PIPE_BUF);
    printf("_POSIX_RE_DUP_MAX = %d\n", _POSIX_RE_DUP_MAX);
    printf("_POSIX_SSIZE_MAX = %d\n", _POSIX_SSIZE_MAX);
    printf("_POSIX_STREAM_MAX = %d\n", _POSIX_STREAM_MAX);
    printf("_POSIX_SYMLINK_MAX = %d\n", _POSIX_SYMLINK_MAX);
    printf("_POSIX_SYMLOOP_MAX = %d\n", _POSIX_SYMLOOP_MAX);
    printf("_POSIX_TTY_NAME_MAX = %d\n", _POSIX_TTY_NAME_MAX);
    printf("_POSIX_TZNAME_MAX = %d\n", _POSIX_TZNAME_MAX);

    printf("2) Значения всех пределов POSIX (2.9)\n");
    printf("ARG_MAX: %d\n", _POSIX_ARG_MAX);
    printf("ATEXIT_MAX: %d\n", 32);
    printf("CHILD_MAX: %d\n", _POSIX_CHILD_MAX);
    printf("DELAYTIMER_MAX: %d\n",_POSIX_DELAYTIMER_MAX);
    printf("HOST_NAME_MAX: %u\n", _POSIX_HOST_NAME_MAX);
    printf("LOGIN_NAME_MAX: %d\n", _POSIX_LOGIN_NAME_MAX);
    printf("OPEN_MAX: %d\n", _POSIX_OPEN_MAX);
    printf("PAGESIZE: %d\n", 1);
    printf("RTSIG_MAX: %d\n", _POSIX_RTSIG_MAX);
    printf("STREAM_MAX: %d\n", _POSIX_STREAM_MAX);
    printf("TIMER_MAX: %d\n", _POSIX_TIMER_MAX);
    printf("TTY_NAME_MAX: %d\n", _POSIX_TTY_NAME_MAX);
    printf("TZNAME_MAX: %d\n", _POSIX_NAME_MAX);

    // значения всех конфигурационных пределов, доступных при компиляции (2.13)
    printf
        ("3) Значения всех конфигурационных пределов, доступных при компиляции \n");
    printf("CHARCLASS_NAME_MAX = %d\n", CHARCLASS_NAME_MAX);
    printf("COLL_WEIGHTS_MAX = %d\n", COLL_WEIGHTS_MAX);
    printf("HOST_NAME_MAX = %d\n", HOST_NAME_MAX);
    printf("LINE_MAX = %d\n", LINE_MAX);
    printf("LOGIN_NAME_MAX = %d\n", LOGIN_NAME_MAX);
    printf("MAX_CANON = %d\n", MAX_CANON);
    printf("MAX_INPUT = %d\n", MAX_INPUT);
    printf("NAME_MAX = %d\n", NAME_MAX);
    printf("NGROUPS_MAX = %d\n", NGROUPS_MAX);
    printf("PATH_MAX = %d\n", PATH_MAX);
    printf("PIPE_BUF = %d\n", PIPE_BUF);
    printf("RE_DUP_MAX = %d\n", RE_DUP_MAX);
    printf("TTY_NAME_MAX = %d\n", TTY_NAME_MAX);

    // значения конфигурационных пределов, получаемых с помощью pathconf(), для корневой файловой системы (2.12)
    printf
        ("4) Значения конфигурационных пределов, получаемых с помощью pathconf(), для корневой файловой системы \n");
    long filesizebits = pathconf("/", _PC_FILESIZEBITS);
    if (filesizebits != -1)
        printf("_PC_FILESIZEBITS: %ld\n", filesizebits);
    else
        perror("pathconf _PC_FILESIZEBITS");

    long linkmax = pathconf("/", _PC_LINK_MAX);
    if (linkmax != -1)
        printf("_PC_LINK_MAX: %ld\n", linkmax);
    else
        perror("pathconf _PC_LINK_MAX");

    long maxcanon = pathconf("/", _PC_MAX_CANON);
    if (maxcanon != -1)
        printf("_PC_MAX_CANON: %ld\n", maxcanon);
    else
        perror("pathconf _PC_MAX_CANON");

    long namemax = pathconf("/", _PC_NAME_MAX);
    if (namemax != -1)
        printf("_PC_NAME_MAX: %ld\n", namemax);
    else
        perror("pathconf _PC_NAME_MAX");

    long pathmax = pathconf("/", _PC_PATH_MAX);
    if (pathmax != -1)
        printf("_PC_PATH_MAX: %ld\n", pathmax);
    else
        perror("pathconf _PC_PATH_MAX");

    long pipebuf = pathconf("/", _PC_PIPE_BUF);
    if (pipebuf != -1)
        printf("_PC_PIPE_BUF: %ld\n", pipebuf);
    else
        perror("pathconf _PC_PIPE_BUF");


    // значения всех конфигурационных пределов, получаемых с помощью sysconf() (2.11)
    printf
        ("5) Значения всех конфигурационных пределов, получаемых с помощью sysconf() \n");
    long argmax = sysconf(_SC_ARG_MAX);
    if (argmax != -1)
        printf("_SC_ARG_MAX: %ld\n", argmax);
    else
        perror("sysconf _SC_ARG_MAX");

    long childmax = sysconf(_SC_CHILD_MAX);
    if (childmax != -1)
        printf("_SC_CHILD_MAX: %ld\n", childmax);
    else
        perror("sysconf _SC_CHILD_MAX");

    long hostname_max = sysconf(_SC_HOST_NAME_MAX);
    if (hostname_max != -1)
        printf("_SC_HOST_NAME_MAX: %ld\n", hostname_max);
    else
        perror("sysconf _SC_HOST_NAME_MAX");

    long ngroups_max = sysconf(_SC_NGROUPS_MAX);
    if (ngroups_max != -1)
        printf("_SC_NGROUPS_MAX: %ld\n", ngroups_max);
    else
        perror("sysconf _SC_NGROUPS_MAX");

    long openmax = sysconf(_SC_OPEN_MAX);
    if (openmax != -1)
        printf("_SC_OPEN_MAX: %ld\n", openmax);
    else
        perror("sysconf _SC_OPEN_MAX");

    long clk_tck = sysconf(_SC_CLK_TCK);
    if (clk_tck != -1)
        printf("_SC_CLK_TCK: %ld\n", clk_tck);
    else
        perror("sysconf _SC_CLK_TCK");

/* Измените с помощью команды ulimit какой-либо из пределов.
 * _SC_OPEN_MAX: 1024
 * ulimit -n 415
 * _SC_OPEN_MAX: 415
 */
}
