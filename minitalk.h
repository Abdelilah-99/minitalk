#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

void    error_exit(char *msg);
void    ft_putnbr(int n);
void    ft_putchar(char c);
void    ft_putstr(char *str);
int     ft_atoi(const char *str);

#endif
