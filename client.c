/* MiniTalk Client */
#include "minitalk.h"

static volatile sig_atomic_t	g_ack;

static void	send_bit(int bit, pid_t pid_server)
{
	g_ack = 0;
	while (!g_ack)
	{
		if (bit == 0)
			kill(pid_server, SIGUSR1);
		else
			kill(pid_server, SIGUSR2);
		usleep(10 * 1000);
		if (g_ack)
			ft_printf(" OK\n");
		else
			ft_printf(" X");
	}
}

static void	ack_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	(void)signum;
	g_ack = 1;
}

static void	init_ack_handler(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	g_ack = 0;
}

static void	send_string(char *str, pid_t pid_server)
{
	int		bit;
	size_t	i;
	int		j;

	i = 0;
	while (i < ft_strlen(str) + 1)
	{
		ft_printf("\nchar '%c':\n", str[i]);
		j = 7;
		while (j >= 0)
		{
			bit = (str[i] >> j) & 1;
			ft_printf("(%d) sent bit : %d ", j, bit);
			send_bit(bit, pid_server);
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
	init_ack_handler();
	if (argc != 3)
	{
		ft_printf("invalid args (1st : Server PID ; 2nd : string to send)\n");
		return (0);
	}
	pid_server = atoi(argv[1]);
	send_string(argv[2], pid_server);
	return (0);
}
