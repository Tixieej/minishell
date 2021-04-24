# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2021/04/24 11:45:45 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
SRC = main.c \
		clear_the_list.c \
		get_next_line.c \
		get_next_line_utils.c \
		gnl_2.c \
		divide_input.c \
		parser.c \
		external.c \
		external_2.c \
		array_functions.c \
		check_type.c \
		echo.c \
		cd.c \
		exit.c \
		export.c \
		export_2.c \
		unset.c \
		error_handler.c \
		linked_struct.c \
		redirection.c \
		pwd.c \
		dup_redirection.c \
		pipes.c \
		signals.c \
		check_env.c \
		expansion.c \
		env.c \
		syntax.c \
		expansion_2.c \
		expansion_3.c \
		prep_redirection.c
OBJ = $(addprefix objs/, $(SRC:.c=.o))
CFLAGS = -Wall -Werror -Wextra
INC = minishell.h get_next_line.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -L. -lft -o $(NAME) $(OBJ)

$(LIBFT):
	cd libft && make bonus
	mv libft/$(LIBFT) .

test: $(NAME)
	./$(NAME)

objs/%.o: srcs/%.c $(INC)
	mkdir -p objs
	$(CC) $(CFLAGS) -Ilibft -I. -c $< -o $@

clean:
	$(RM) $(OBJ)
	cd libft && make clean

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)

re: fclean all
