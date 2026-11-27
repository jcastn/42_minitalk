/* MiniTalk Server */
#include "minitalk.h"

static t_dyntab	g_tab;

static void	alloc_dyntab(void)
{
	if (g_tab.size != 0)
		free(g_tab.data);
	g_tab.size = 4;
	g_tab.data = ft_calloc(g_tab.size, sizeof(char));
	g_tab.count = 0;
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	int		pos;
	pid_t	pid_client;

	(void)context;
	(void)info;
	pos = g_tab.count;
	g_tab.data[pos] = (g_tab.data[pos] << 1) | (signum == SIGUSR2);
	pid_client = info->si_pid;
	kill(pid_client, SIGUSR1);
}

static void	init_server(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	alloc_dyntab();
}

int	main(void)
{
	int		i;

	ft_printf("MiniTalk Server (PID : %d)\n", getpid());
	init_server();
	while (1)
	{
		i = 0;
		while (i < 8)
		{
			pause();
			i++;
		}
		if (g_tab.count >= g_tab.size - 1)
		{
			g_tab.data = ft_realloc(g_tab.data, g_tab.size, g_tab.size * 2);
			g_tab.size *= 2;
		}
		if (g_tab.data[g_tab.count] == '\0')
		{
			ft_printf("%s\n", g_tab.data);
			alloc_dyntab();
		}
		else
			g_tab.count++;
	}
}
