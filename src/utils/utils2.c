/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../../libs/my_ftp.h"

void trim(char *str)
{
    char *start = str;
    char *end = str + strlen(str) - 1;

    while (isspace(*start)) {
        start++;
    }
    while (end > start && isspace(*end)) {
        end--;
    }
    *(end + 1) = '\0';
    if (start != str) {
        memmove(str, start, end - start + 2);
    }
}

int found_end(char *str)
{
    size_t i;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '\r' && (i + 1) <= strlen(str) &&
            str[i + 1] == '\n') {
            return 1;
        }
    }
    return 0;
}
