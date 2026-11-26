LIBFT = ./libft_upgraded/libft.a
LIBFT_DIR = ./libft_upgraded/
CC = cc
FLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -g -fsanitize=address

all : client server 

$(LIBFT):
	make -C $(LIBFT_DIR) all

client: client.c minitalk.h $(LIBFT)
	$(CC) $(FLAGS) client.c $(LIBFT) -o client

server: server.c minitalk.h $(LIBFT)
	$(CC) $(FLAGS) server.c $(LIBFT) -o server

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf server client

fclean :
	make -C $(LIBFT_DIR) fclean
	rm -rf server client

re : fclean all

.PHONY: all clean fclean re
