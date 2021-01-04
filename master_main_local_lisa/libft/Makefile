# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: livlamin <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/30 16:41:57 by livlamin       #+#    #+#                 #
#    Updated: 2019/12/03 09:35:45 by livlamin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE = .

SRC =		ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_isdigit.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c

BONUS_SRC =	ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c


ifdef WITH_BONUS
OBJECT = $(SRC:.c=.o) $(BONUS_SRC:.c=.o)
else
OBJECT = $(SRC:.c=.o)
endif

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE)

vpath %.c .

all: $(NAME)

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@ $(MAKE) WITH_BONUS=1 all

clean:
	$(RM) $(SRC:.c=.o) $(BONUS_SRC:.c=.o)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: clean fclean
