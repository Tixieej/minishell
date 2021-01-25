# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/13 10:40:20 by rde-vrie      #+#    #+#                  #
#    Updated: 2020/11/26 13:22:23 by rixt          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
SRC = main.c \
		get_next_line.c \
		get_next_line_utils.c \
		start_program.c \
		parser.c \
		parse.c \
		non_buildin.c \
		env_path.c \
		check_type.c \
		echo.c \
		cd.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
CC = gcc
INC = minishell.h get_next_line.h
all: $(NAME)
$(NAME): $(LIBFT) $(OBJ)
	$(CC) -L. -lft -o $(NAME) $(OBJ)
$(LIBFT):
	cd libft && make bonus
	mv libft/$(LIBFT) .
test: $(NAME)
	./$(NAME)
%.o: %.c $(INC)
	$(shell mkdir -p $(dir $@))
	gcc $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)
	cd libft && make clean
fclean:	clean
	$(RM) $(NAME)
	rm -rf $(LIBFT)
re: fclean all

# NAME = minishell
# LIBFT = libft/libft.a
# SRC = main.c \
# 		get_next_line.c \
# 		get_next_line_utils.c \
# 		ft_list_push_back.c \
# 		ft_create_elem.c
# OBJ = $(SRC:.c=.o)
# CFLAGS = -Wall -Werror -Wextra
# CC = gcc
# INC = minishell.h get_next_line.h

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ) minishell.h
# 	$(CC) -Llibft -o $(NAME) $(OBJ)

# $(LIBFT):
# 	$(MAKE) -C $(dir $(LIBFT)) all

# test: $(NAME)
# 	./$(NAME)

# %.o: %.c $(INC)
# 	$(shell mkdir -p $(dir $@))
# 	gcc $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJ)
# 	$(MAKE) -C $(dir $(LIBFT)) clean

# fclean:	clean
# 	$(RM) $(NAME)
# 	$(MAKE) -C $(dir $(LIBFT)) fclean

# re: fclean all
