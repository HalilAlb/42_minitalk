/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:02:40 by malbayra          #+#    #+#             */
/*   Updated: 2025/01/29 17:31:08 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk_bonus.h"

static int is_message_received = 0;  // Global değişken

void	ft_send_str(int pid, char *str)
{
	static int	bit_index = 0;
	static char	*message = 0;
	char		current_char;
	int			current_bit;

	if (str)
		message = str;
	if (message && message[bit_index / 8])
	{
		current_char = message[bit_index / 8];
		current_bit = (current_char >> (bit_index % 8)) & 1;
		if (current_bit == 1 && kill(pid, SIGUSR2) == -1)
			ft_printf("%s", "Error KILL\n");
		else if (current_bit == 0 && kill(pid, SIGUSR1) == -1)
			ft_printf("%s", "Error KILL\n");
		bit_index++;
	}
	else if (message)
	{
		while (bit_index++ <= 8)
			if (kill(pid, SIGUSR1) == -1)
				ft_printf("%s", "Error KILL\n");
		exit(0);
	}
}

void	ft_receipt(int sig, siginfo_t *info, void *context)
{
	static int	pid = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		ft_send_str(pid, NULL);
	else if (sig == SIGUSR2)
	{
		// Mesaj alındı, client bu durumu yazacak
		if (!is_message_received)  // Global değişken kontrolü
		{
			ft_printf("Mesaj alindi\n");
		}
		exit(0);  // Client sonlanacak
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	if (ac != 3)
		ft_printf("Usage: ./client <PID> <String>");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_receipt;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_printf("%s", "SIGACTION");

	ft_send_str(ft_atoi(av[1]), av[2]);

	while (1)
		pause();
	return (0);
}

