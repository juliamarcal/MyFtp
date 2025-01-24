/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libs/my_ftp.h"

char *check_login_cmds(char *command, char *command_line,
    my_client_t *client, my_server_t *server)
{
    if (strcmp(command, "USER") == 0)
        return cmd_user(command_line, client);
    if (strcmp(command, "PASS") == 0)
        return cmd_pass(command_line, client);
    if (strcmp(command, "CWD") == 0)
        return cmd_cwd(command_line, server);
    if (strcmp(command, "CDUP") == 0)
        return cmd_cdup(server);
    if (strcmp(command, "QUIT") == 0)
        return cmd_quit(client);
    return "";
}

char *check_file_action(char *command, char *command_line)
{
    if (strcmp(command, "STOR") == 0)
        return "command not found2";
    if (strcmp(command, "RETR") == 0)
        return "command not found2";
    if (strcmp(command, "LIST") == 0)
        return cmd_list();
    if (strcmp(command, "DELE") == 0)
        return cmd_dele(command_line);
    if (strcmp(command, "PWD") == 0)
        return cmd_pwd();
    return "";
}

char *check_others(char *command, char *command_line, my_server_t *server)
{
    if (strcmp(command, "HELP") == 0)
        return cmd_help();
    if (strcmp(command, "NOOP") == 0)
        return cmd_noop();
    if (strcmp(command, "PORT") == 0)
        return cmd_port(command_line, server);
    if (strcmp(command, "PASV") == 0)
        return cmd_pasv(server);
    return "";
}
