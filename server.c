#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int  bit_count;
	static char c;

	bit_count = 0;
	c = 0;
	(void)context;
	if (sig == SIGUSR2)
		c |= (1 << bit_count);
	kill(info->si_pid, SIGUSR1);
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
