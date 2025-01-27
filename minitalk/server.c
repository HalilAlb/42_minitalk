/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:01:31 by malbayra          #+#    #+#             */
/*   Updated: 2025/01/27 15:42:28 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error(const char *msg)
{
	ft_printf("%s", msg);
	exit(1);
}

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bit;

	(void)context;
	c |= (sig == SIGUSR2) << bit++;
	if (bit == 8)
	{
		if (c > 127)
		{
			c = 0;
			bit = 0;
			kill(info->si_pid, SIGUSR1);
			return ;
		}
		if (c == 0)
			kill(info->si_pid, SIGUSR2);
		else
			ft_printf("%c", c);
		c = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_error("Signal Error\n");
	ft_printf("PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
