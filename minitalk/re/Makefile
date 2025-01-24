NAME = libftprintf.a

SRCS = ft_func.c  ft_funk.c ft_printf.c\

OBJ =$(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	

.PHONY: all clean fclean re