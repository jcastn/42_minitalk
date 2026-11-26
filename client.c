/* MiniTalk Client */
#include "minitalk.h"

bool	get_ack(pid_t pid_client)
{
	(void)pid_client;
	//ft_printf("X");
	ft_printf(" OK\n");
	return (true);
}

void	send_string(char *str, pid_t pid_server)
{
	int		bit;
	size_t 	i;
	int 	j;
	int		c;

	i = 0;
	while (i < ft_strlen(str) + 1)
	{
		ft_printf("\nchar '%c' :\n", str[i]);
		c = str[i];
		j = 7;
		while (j >= 0)
		{
			bit = (c >> j) & 1;
			ft_printf("(%d) sent bit : %d\n", j, bit);
		//	ack = false;
			//while (!ack)
			{
				usleep(10 * 100);
				if (bit == 0)
					kill(pid_server, SIGUSR1);
				else
					kill(pid_server, SIGUSR2);
	//			ack = get_ack(pid_server);
			}
			j--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid_server;
	pid_t	pid_client;

	pid_client = getpid();
	ft_printf("MiniTalk Client\n");
	ft_printf("Client PID : %d\n", pid_client);
	if (argc != 3)
	{
		ft_printf("invalid args (1st : Server PID ; 2nd : string to send)\n");
		return (0);
	}
	pid_server = atoi(argv[1]);
	send_string(argv[2], pid_server);
	return (0);
}
