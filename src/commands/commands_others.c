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

char *cmd_port(char *command_line, my_server_t *server)
{
    struct sockaddr_in server_addr;
    char *arg = get_second_arg(command_line);

    if (parse_port_command(arg, server) == 1)
        return "501 Syntax error in parameters or arguments.\n";
    server->data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->data_socket < 0)
        show_error("Error creating socket");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->data_port);
    inet_pton(AF_INET, server->data_ip_address, &server_addr.sin_addr);
    if (connect(server->data_socket, (struct sockaddr *)&server_addr,
    sizeof(server_addr)) < 0) {
        perror("Error connecting to client");
        close(server->data_socket);
        return "425 Can't open data connection.\n";
    }
    return "200 PORT command successful. Waiting for data connection.\n";
}

char *cmd_pasv(my_server_t *server)
{
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char *response;

    if (create_data_socket(server) < 0)
        return "425 Can't open data connection.\n";
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind_data_socket(server, &server_addr) < 0)
        return "425 Can't open data connection.\n";
    if (get_and_store_port(server, &server_addr, &addr_len) < 0)
        return "425 Can't open data connection.\n";
    response = generate_pasv_response(server);
    if (listen(server->data_socket, 1) < 0) {
        close(server->data_socket);
        return "425 Can't open data connection.\n";
    }
    return response;
}

char *cmd_help(void)
{
    return (
        "214 type any command\n");
}

char *cmd_noop(void)
{
    return "200 Command okay.\n";
}
