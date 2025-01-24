/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "../../libs/my_ftp.h"

int parse_port_command(char *arg, my_server_t *server)
{
    char *token;
    int port;

    if (count_commas(arg) != 5)
        return 1;
    token = strtok(arg, ",");
    strcat(server->data_ip_address, token);
    strcat(server->data_ip_address, ".");
    for (int i = 0; i < 3; i++) {
        token = strtok(NULL, ",");
        strcat(server->data_ip_address, token);
        if (i == 2)
            break;
        strcat(server->data_ip_address, ".");
    }
    token = strtok(NULL, ",");
    port = atoi(token) * 256;
    token = strtok(NULL, ",");
    server->data_port = port + atoi(token);
    return 0;
}

char *generate_pasv_response(my_server_t *server)
{
    char response[256];

    snprintf(response, sizeof(response),
        "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d).\n",
        (int)(server->data_ip_address[0] & 0xFF),
        (int)(server->data_ip_address[1] & 0xFF),
        (int)(server->data_ip_address[2] & 0xFF),
        (int)(server->data_ip_address[3] & 0xFF),
        server->data_port / 256,
        server->data_port % 256);
    return strdup(response);
}

int create_data_socket(my_server_t *server)
{
    server->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->data_socket < 0)
        return -1;
    return 0;
}

int bind_data_socket(my_server_t *server,
    struct sockaddr_in *server_addr)
{
    if (bind(server->data_socket, (struct sockaddr *)server_addr,
        sizeof(*server_addr)) < 0) {
        close(server->data_socket);
        return -1;
    }
    return 0;
}

int get_and_store_port(my_server_t *server, struct sockaddr_in *server_addr,
    socklen_t *addr_len)
{
    if (getsockname(server->data_socket,
        (struct sockaddr *)server_addr, addr_len) < 0) {
        close(server->data_socket);
        return -1;
    }
    server->data_port = ntohs(server_addr->sin_port);
    return 0;
}
