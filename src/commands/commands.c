/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../libs/my_ftp.h"

void delete_specific_sequence(char *str)
{
    char *src = str;
    char *dst = str;

    while (*src != '\0') {
        if (strncmp(src, "^M$", 3) == 0) {
            src += 3;
            continue;
        }
        if (strncmp(src, "\r\n", 2) == 0) {
            src += 2;
            continue;
        }
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
}

char *get_second_arg(char *line)
{
    size_t i;
    char *arg;
    int num_spaces = 0;
    size_t length = strlen(line);

    for (i = 0; i < length; i++) {
        if (num_spaces == 1)
            break;
        if (line[i] == ' ')
            num_spaces++;
    }
    if (num_spaces != 1)
        return strdup("");
    arg = (char *)malloc(length - i + 1);
    if (arg == NULL)
        show_error("Error in memory allocation.\n");
    strncpy(arg, line + i, length - i);
    arg[length - i] = '\0';
    return arg;
}

char *get_command(char *command_line)
{
    size_t i;
    char *command;
    size_t length = strlen(command_line);

    for (i = 0; i < length; i++) {
        if (command_line[i] == ' ') {
            break;
        }
    }
    command = (char *)malloc(i + 1);
    if (command == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(command, command_line, i);
    command[i] = '\0';
    return command;
}

char *do_command(char *command_line, my_client_t *client, my_server_t *server)
{
    char *command = get_command(command_line);
    char *result_str = (char *)malloc(1024 * sizeof(char));

    to_upper_case(command);
    strcpy(result_str, check_cli_login(command, client));
    if (strcmp(result_str, "") != 0)
        return result_str;
    strcpy(result_str, check_login_cmds(command, command_line,
    client, server));
    if (strcmp(result_str, "") != 0)
        return result_str;
    strcpy(result_str, check_file_action(command, command_line));
    if (strcmp(result_str, "") != 0)
        return result_str;
    strcpy(result_str, check_others(command, command_line, server));
    if (strcmp(result_str, "") != 0)
        return result_str;
    free(result_str);
    return "500 Syntax error, command unrecognized.\n";
}

char *check_cli_login(char *command, my_client_t *client)
{
    if (client->is_loged_in != 2 && (strcmp(command, "CWD") == 0 ||
    strcmp(command, "CDUP") == 0 || strcmp(command, "QUIT") == 0 ||
    strcmp(command, "STOR") == 0 || strcmp(command, "RETR") == 0 ||
    strcmp(command, "LIST") == 0 || strcmp(command, "DELE") == 0 ||
    strcmp(command, "PWD") == 0 || strcmp(command, "PORT") == 0 ||
    strcmp(command, "PASV") == 0)) {
        return "530 Not logged in.\n";
    } else {
        return "";
    }
}
