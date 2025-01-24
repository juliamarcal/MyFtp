##
## EPITECH PROJECT, 2024
## Network
## File description:
## My_ftp
##

##
## EPITECH PROJECT, 2024
## Network
## File description:
## My_ftp
##

NAME = myftp

CC = gcc

RM = rm -f

CFLAGS += -W -Wall -Wextra -Werror -std=gnu99 -I ./libs

SRCS = src/server.c \
		src/main.c \
		src/commands_check.c \
		src/utils/utils2.c \
		src/utils/utils.c \
		src/commands/file_modes_util.c \
		src/commands/commands.c \
		src/commands/commands_others.c \
		src/commands/commands_login.c \
		src/commands/commands_file_action.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
