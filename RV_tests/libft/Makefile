# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rde-vrie <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/30 09:41:57 by rde-vrie      #+#    #+#                  #
#    Updated: 2019/12/12 10:30:20 by rde-vrie      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
	ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_toupper.c ft_tolower.c ft_strdup.c ft_calloc.c \
	ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OFILES = $(SRC:.c=.o)
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstmap_bonus.c
OBONUS = $(BONUS:.c=.o)
HEADER = libft.h
FLAGS = -Wall -Werror -Wextra

ifdef WITH_BONUS
OBJ_FILES = $(OFILES) $(OBONUS)
else
OBJ_FILES = $(OFILES)
endif

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rc $(NAME) $(OBJ_FILES)

%.o: %.c $(HEADER)
	gcc -c $(FLAGS) -I. -o $@ $<

bonus:
	$(MAKE) WITH_BONUS=1 all

clean:
	$(RM) $(OFILES) $(OBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
