/*
** EPITECH PROJECT, 2024
** Network
** File description:
** My_ftp
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libs/my_ftp.h"

void print_help(void)
{
    printf("USAGE: ./myftp port path\n");
    printf("       ");
    printf("port is the port number on which the server socket listens\n");
    printf("       ");
    printf("path is the path to the home directory for the Anonymous user\n");
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        print_help();
    } else if (argc == 3) {
        start_server(atoi(argv[1]), argv[2]);
    } else {
        print_help();
        exit(84);
    }
    return 0;
}
