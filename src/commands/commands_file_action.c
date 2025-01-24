/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../libs/my_ftp.h"

// char *cmd_stor(char *command_line)
// {

// }

// char *cmd_retr(char *command_line)
// {

// }
char *cmd_list(void)
{
    char *response = strdup("150 Here comes the directory listing.\n");
    DIR *dir;
    struct dirent *entry;
    char buffer[1024];

    dir = opendir(".");
    if (dir == NULL)
        return "550 Failed to open directory.\n";
    entry = readdir(dir);
    while (entry != NULL) {
        sprintf(buffer, "%s\n", entry->d_name);
        response = realloc(response, (strlen(response) + strlen(buffer) + 1));
        if (strcmp(buffer, ".\n") != 0 && strcmp(buffer, "..\n") != 0)
            strcat(response, buffer);
        entry = readdir(dir);
    }
    closedir(dir);
    response = realloc(response, strlen(response) + 26);
    strcat(response, "226 Directory send OK.\n");
    return response;
}

char *cmd_dele(char *command_line)
{
    char *file_path = get_second_arg(command_line);

    if (file_path == NULL || strlen(file_path) == 0) {
        return "501 Syntax error in parameters or arguments.\n";
    }
    if (remove(file_path) == 0) {
        return "250 Requested file action okay, completed.\n";
    } else {
        return "550 Requested action not taken. File unavailable.\n";
    }
}

char *cmd_pwd(void)
{
    char path[4096] = {0};
    char *response;

    if (getcwd(path, 4096)) {
        response = (char *)malloc(strlen(path) + 100);
        if (response != NULL) {
            sprintf(response, "257 \"%s\" is the current directory.\n", path);
            return response;
        }
        return strdup("451 Requested action aborted: \
        local error in processing.\n");
    }
    return strdup("501 Syntax error in parameters or arguments.\n");
}
