/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libs/my_ftp.h"

char *cmd_user(char *command_line, my_client_t *client)
{
    char *user = get_second_arg(command_line);

    to_upper_case(user);
    if (client->is_loged_in == 2) {
        free(user);
        return "230 User logged in, proceed\n";
    }
    if (client->is_loged_in <= 1) {
        client->is_loged_in = 1;
        strcpy(client->user, user);
        free(user);
        return "331 User name okay, need password\n";
    }
    free(user);
    return "501 Syntax error in parameters or arguments.\n";
}

char *cmd_pass(char *command_line, my_client_t *client)
{
    char *password = get_second_arg(command_line);

    to_upper_case(password);
    if (client->is_loged_in == 2 ||
    (client->is_loged_in == 1 && strcmp(password, "") == 0 &&
        strcmp(client->user, "ANONYMOUS") == 0)) {
        client->is_loged_in = 2;
        strcpy(client->pass, "");
        free(password);
        return "230 User logged in, proceed\n";
    }
    if (client->is_loged_in == 0) {
        free(password);
        return "332 Need account for login.\n";
    }
    free(password);
    return "501 Syntax error in parameters or arguments.\n";
}

char *cmd_cwd(char *command_line, my_server_t *server)
{
    char *path = get_second_arg(command_line);

    if (path == NULL) {
        free(path);
        return "501 Syntax error in parameters or arguments.\n";
    }
    if (chdir(path) == 0) {
        strcpy(server->path, path);
        free(path);
        return "250 Requested file action okay, completed.\n";
    } else {
        return "550 Requested action not taken. \
        File unavailable (e.g., file not found, no access).\n";
    }
}

char *cmd_cdup(my_server_t *server)
{
    if (chdir("..") == 0) {
        strcpy(server->path, getcwd(NULL, 0));
        return "200 Command okay.\n";
    } else {
        return "550 Requested action not taken. File unavailable \
        (e.g., file not found, no access).\n";
    }
}

char *cmd_quit(my_client_t *client)
{
    client->is_loged_in = 0;
    return "Service closing control connection. \
    Logged out if appropriate.\n";
}
