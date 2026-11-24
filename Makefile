FLAGS = -Wall -Wextra -Werror
CC = cc

all : client server

client: client.c
	$(CC) $(FLAGS) client.c -o client

server: server.c
	$(CC) $(FLAGS) server.c -o server

clean :
	rm -rf server client

fclean : clean

re : fclean all

.PHONY: all clean fclean re
