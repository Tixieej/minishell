# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rixt <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/21 14:25:14 by rixt          #+#    #+#                  #
#    Updated: 2021/01/12 10:57:21 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minitests
SRC = main.c get_next_line.c get_next_line_utils.c env_path.c\
		ft_list_push_back.c ft_create_elem.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
INC = minishell.h get_next_line.h ft_list.h
LIBFT = libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -L. -lft -o $(NAME) $(OBJ)

test: $(NAME)
	./$(NAME)

$(LIBFT):
	cd libft && make
	mv libft/$(LIBFT) .

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -Ilibft -I. -c $< -o $@

clean: 
	$(RM) $(OBJ) exec_cp.o
	cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)

re: fclean all
