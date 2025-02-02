#include "minitalk.h"

int	msg_is_received = 0;

static void	is_data_arrived(int sig)
{
	(void)sig;
	msg_is_received = 1;
}

static void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		msg_is_received = 0;
		if ((c & (1 << bit)))
		{
			if (kill(pid, SIGUSR2) == -1)
				error_exit("Error: Failed to send SIGUSR2.");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				error_exit("Error: Failed to send SIGUSR1.");
		}
		while (!msg_is_received)
			usleep(50);
		bit++;
	}
	usleep(50);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		error_exit("Usage: ./client <server_pid> <message>");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		error_exit("Error: Invalid PID");
	sa.sa_handler = is_data_arrived;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_exit("Error: Could not setup signal handler");
	i = 0;
	while (argv[2][i])
		send_char(server_pid, argv[2][i++]);
	send_char(server_pid, '\0');
	return (0);
}
