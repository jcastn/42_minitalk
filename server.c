
/* MiniTalk Server */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static char g_byte;

void signal_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_byte = (g_byte << 1);
	}
	else if (signum == SIGUSR2)
	{
		g_byte = (g_byte << 1) | 1;
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(void)
{
	struct sigaction sa;
	int i;
	pid_t pid;

	pid = getpid();
	printf("MiniTalk Server (PID : %d)\n", pid);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		i = 0;
		g_byte = 0;
		while (i < 8)
		{
			pause();
			// printf("received value : %d\n", received_signal);
			i++;
		}
		if (g_byte == '\0')
			write(1, "\n", 1);
		write(1, &g_byte, 1);
	}
}
