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
#pragma once

typedef struct my_server_t {
    int svr_socket;
    int port;
    char *path;
    char data_ip_address[16];
    int data_port;
    int data_socket;
} my_server_t;

typedef struct my_client_t {
    int is_loged_in;
    char user[100];;
    char pass[100];
} my_client_t;

// server functions
void start_server(int port, char *path);
void listen_for_connections(my_server_t *server);
void server_loop(my_server_t *server);

// command related functions
char *do_command(char *command_line, my_client_t *client, my_server_t *server);
char *get_command(char *command_line);
char *get_second_arg(char *line);
char *check_cli_login(char *command, my_client_t *client);
void delete_specific_sequence(char *str);

// command check functions
char *check_others(char *command, char *command_line, my_server_t *server);
char *check_file_action(char *command, char *command_line);
char *check_login_cmds(char *command, char *command_line,
    my_client_t *client, my_server_t *server);

// login and logout
char *cmd_user(char *command_line, my_client_t *client);
char *cmd_pass(char *command_line, my_client_t *client);
char *cmd_cwd(char *command_line, my_server_t *server);
char *cmd_cdup(my_server_t *server);
char *cmd_quit(my_client_t *client);

// file action
char *cmd_stor(char *command_line);
char *cmd_retr(char *command_line);
char *cmd_list(void);
char *cmd_dele(char *command_line);
char *cmd_pwd(void);

// others
char *cmd_port(char *command_line, my_server_t *server);
char *cmd_pasv(my_server_t *server);
char *cmd_help(void);
char *cmd_noop(void);

// file modes util
int parse_port_command(char *arg, my_server_t *server);
char *generate_pasv_response(my_server_t *server);
int create_data_socket(my_server_t *server);
int bind_data_socket(my_server_t *server, struct sockaddr_in *server_addr);
int get_and_store_port(my_server_t *server,
    struct sockaddr_in *server_addr, socklen_t *addr_len);

//utils
void show_error(char *error);
my_server_t start_server_struct(int port, char *path, int svr_socket);
my_client_t start_client_struct(void);
void to_upper_case(char *str);
int count_commas(char *line);
void trim(char *str);
int found_end(char *str);
