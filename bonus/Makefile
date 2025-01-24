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

SRCS =	$(wildcard ./*.c)

OBJS =	$(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
