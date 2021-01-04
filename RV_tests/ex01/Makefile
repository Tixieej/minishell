# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rixt <marvin@codam.nl>                       +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/21 14:25:14 by rixt          #+#    #+#                  #
#    Updated: 2021/01/04 10:25:42 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minitests
SRC = main.c get_next_line.c get_next_line_utils.c ft_split.c ft_list_push_back.c ft_create_elem.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
INC = minishell.h get_next_line.h ft_list.h
EXEC = exec

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

test: $(NAME)
	./$(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJ) exec_cp.o

fclean: clean
	$(RM) $(NAME) $(EXEC)

re: fclean all

exec: exec_cp.o
	#$(CC) $(CFLAGS) -c $< -o $@
	$(CC) -o $(EXEC) exec_cp.o
	./$(EXEC)
