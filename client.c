/* MiniTalk Client */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	send_string(char *str, pid_t pid)
{
	int		bit;
	int 	i;
	int 	j;
	int		c;

	i = 0;
	while (i < ft_strlen(str) + 1)
	{
		printf("\nchar '%c' :\n", str[i]);
		c = str[i];
		j = 7;
		while (j >= 0)
		{
			bit = (c >> j) & 1;
			printf("sent bit : %d\n", bit);
			usleep(10 * 1000);
			if (bit == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			j--;
		}
		i++;
	}
}


int	main(int argc, char **argv)
{
	pid_t	pid;

	printf("MiniTalk Client\n");
	if (argc != 3)
	{
		printf("invalid args (1st : Server PID ; 2nd : string to send)\n");
		return (0);
	}
	pid = atoi(argv[1]);
	send_string(argv[2], pid);
	return (0);
}
