/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../../libs/my_ftp.h"

void show_error(char *error)
{
    perror(error);
    exit(84);
}

my_server_t start_server_struct(int port, char *path, int svr_socket)
{
    my_server_t server;

    server.port = port;
    server.path = path;
    server.svr_socket = svr_socket;
    server.data_port = -1;
    server.data_socket = -1;
    server.data_ip_address[0] = '\0';
    return server;
}

my_client_t start_client_struct(void)
{
    my_client_t cli;

    cli.is_loged_in = 0;
    return cli;
}

void to_upper_case(char *str)
{
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

int count_commas(char *line)
{
    int count = 0;
    size_t i;

    for (i = 0; i < strlen(line); i++) {
        if (line[i] == ',')
            count++;
    }
    return count;
}
