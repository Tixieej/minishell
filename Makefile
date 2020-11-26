# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2020/11/26 10:02:57 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c
OBJ = $(addprefix objs/, $(SRC:.c=.o))
CFLAGS = -Wall -Werror -Wextra
CC = gcc
LIBFT = libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -L. -lmlx -lft -o $(NAME) $(OBJ)

test: $(NAME)
	./$(NAME)

$(LIBFT):
	cd libft && make
	mv libft/$(LIBFT) .

objs/%.o: srcs/%.c minishell.h
	mkdir -p objs
	gcc $(CFLAGS) -Ilibft -I. -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd libft && make clean

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)

re: fclean all
