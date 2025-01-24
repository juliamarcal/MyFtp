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
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../libs/my_ftp.h"

void send_message(int client_socket, const char *message)
{
    int message_length = strlen(message);
    int bytes_written = write(client_socket, message, message_length);

    if (bytes_written < 0) {
        show_error("Write failed");
    } else if (bytes_written != message_length) {
        show_error("Incomplete message written\n");
    } else {
        printf("message sent: %s", message);
    }
}

void handle_client_input(int client_socket, my_server_t *server)
{
    char buffer[1024] = "\0";
    int bytes_received;
    char command[2048] = "";
    my_client_t client = start_client_struct();

    while (1) {
        bytes_received = read(client_socket, buffer, 1024);
        if (bytes_received == 0)
            break;
        buffer[bytes_received] = '\0';
        strcat(command, buffer);
        while (found_end(command) == 0) {
            bytes_received = read(client_socket, buffer, 1024);
            buffer[bytes_received] = '\0';
            strcat(command, buffer);
        }
        delete_specific_sequence(command);
        send_message(client_socket, do_command(command, &client, server));
        command[0] = '\0';
    }
}

void server_loop(my_server_t *server)
{
    pid_t pid;
    struct sockaddr_in client_addr;
    int new_socket;
    int addrlen = sizeof(client_addr);

    while (1) {
        new_socket = accept(server->svr_socket,
            (struct sockaddr *)&client_addr, (socklen_t *)&addrlen);
        if (new_socket < 0)
            show_error("Accept failed");
        else
            send_message(new_socket, "220 Service ready for new user\n");
        pid = fork();
        if (pid < 0)
            show_error("Fork failed");
        if (pid == 0)
            handle_client_input(new_socket, server);
        else
            close(new_socket);
    }
}

void listen_for_connections(my_server_t *server)
{
    if (listen(server->svr_socket, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening for connections...\n");
    server_loop(server);
}

void start_server(int port, char *path)
{
    int svr_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    int binded;
    my_server_t server = start_server_struct(port, path, svr_socket);
    int reuse = 1;

    if (svr_socket == -1)
        show_error("Error creating socket");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(server.port);
    setsockopt(server.svr_socket, SOL_SOCKET, SO_REUSEADDR,
    &reuse, sizeof(reuse));
    binded = bind(server.svr_socket,
    (struct sockaddr *)&address, sizeof(address));
    if (binded < 0)
        show_error("Error binding the socket to the correct address");
    if (chdir(path) != 0)
        show_error("Invalid path");
    listen_for_connections(&server);
}
