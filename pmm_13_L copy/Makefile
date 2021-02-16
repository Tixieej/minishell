# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2021/02/15 11:45:31 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
SRC = main.c \
		get_next_line.c \
		get_next_line_utils.c \
		divide_input.c \
		parser.c \
		external.c \
		env_path.c \
		check_type.c \
		echo.c \
		cd.c \
		exit.c \
		error_handler.c \
		linked_struct.c \
		redirection.c \
		pwd.c \
		dup_redirection.c \
		pipes.c \
		signals.c \
		check_env.c \
		REMOVE_HULPFUNCTIE.c
		
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
INC = minishell.h get_next_line.h
ifdef DEBUG
CFLAGS += -g -fsanitize=address
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -L. -lft -o $(NAME) $(OBJ)

$(LIBFT):
	cd libft && make bonus
	mv libft/$(LIBFT) .

test: $(NAME)
	./$(NAME)

%.o: %.c $(INC)
	$(shell mkdir -p $(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd libft && make clean

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)

re: fclean all
