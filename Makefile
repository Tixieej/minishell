# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2020/11/26 10:19:39 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

test: $(NAME)
	./$(NAME)

%.o: %.c minishell.h
	gcc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re: fclean all
