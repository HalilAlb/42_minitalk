
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f


SRCS_SERVER = server.c
SRCS_CLIENT = client.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)


SRCS_SERVER_BONUS = server_bonus.c
SRCS_CLIENT_BONUS = client_bonus.c
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)


NAME_SERVER = server
NAME_CLIENT = client
NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus


LIBFTDIR    = libft
LIBFT       = $(LIBFTDIR)/libft.a
PRINTF_DIR  = $(LIBFTDIR)/ft_printf
PRINTF      = $(PRINTF_DIR)/libftprintf.a


all: $(LIBFT) $(PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

bonus: $(LIBFT) $(PRINTF) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)


$(LIBFT):
	@make -C $(LIBFTDIR)


$(PRINTF):
	@make -C $(PRINTF_DIR)


$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)


$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)


$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_SERVER_BONUS)


$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT_BONUS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(PRINTF_DIR)
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(PRINTF_DIR)
	$(RM) $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
