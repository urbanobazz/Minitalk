SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
HFILE = minitalk.h
LIBFTDIR = ./libft
LIBFT = libft/libft.a
INCLUDE = -L ./libft -lft

all: $(SERVER) $(CLIENT)

$(SERVER) $(CLIENT): $(LIBFT)
				$(CC) $(CFLAGS) server.c $(INCLUDE) -o $(SERVER)
				$(CC) $(CFLAGS) client.c $(INCLUDE) -o $(CLIENT)

$(LIBFT):
		@make -C ./libft

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS) $(CLIENT_BONUS): $(LIBFT)
	$(CC) $(CFLAGS) server_bonus.c $(INCLUDE) -o $(SERVER_BONUS)
	$(CC) $(CFLAGS) client_bonus.c $(INCLUDE) -o $(CLIENT_BONUS)

clean:
	@make clean -C $(LIBFTDIR)

fclean: clean
	@make fclean -C $(LIBFTDIR)
	@rm -f $(SERVER) $(CLIENT)
	@rm -f $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all
