/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:02:40 by malbayra          #+#    #+#             */
/*   Updated: 2025/01/30 06:28:41 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	send_bit(int pid, int bit)
{
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			printf("Hata: kill(SIGUSR2)\n");
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			printf("Hata: kill(SIGUSR1)\n");
	}
}

static void	send_null_terminator(int pid, int *sent)
{
	if (*sent < 8)
	{
		send_bit(pid, 0);
		(*sent)++;
	}
	else
		exit(0);
}

static void	ft_send_str(int pid, const char *str)
{
	static const char	*message = NULL;
	static int			bit_index = 0;
	static int			null_bits_sent = 0;
	char				current_char;
	int					current_bit;

	if (str)
	{
		message = str;
		bit_index = 0;
		null_bits_sent = 0;
	}
	if (message && message[bit_index / 8] != '\0')
	{
		current_char = message[bit_index / 8];
		current_bit = (current_char >> (bit_index % 8)) & 1;
		send_bit(pid, current_bit);
		bit_index++;
	}
	else if (message)
		send_null_terminator(pid, &null_bits_sent);
}

void	ft_receipt(int sig, siginfo_t *info, void *context)
{
	static int	pid = 0;

	(void)context;
	if (info->si_pid != 0)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		ft_send_str(pid, NULL);
	else if (sig == SIGUSR2)
	{
		printf("Mesaj sunucu tarafından başarıyla alındı.\n");
		exit(0);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int					server_pid;

	if (ac != 3)
	{
		if (ac < 3)
			printf("HATA: yetersiz argüman\n");
		else
			printf("HATA: fazla argüman\n");
		printf("KULLANIM: ./client <sunucu_pid> <string>\n");
		return (1);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &ft_receipt;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		printf("HATA: sigaction\n");
		return (1);
	}
	server_pid = atoi(av[1]);
	ft_send_str(server_pid, av[2]);
	while (1)
		pause();
}
