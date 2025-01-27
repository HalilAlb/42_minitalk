// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   server_bonus.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/24 17:07:32 by malbayra          #+#    #+#             */
// /*   Updated: 2025/01/27 12:15:46 by malbayra         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minitalk_bonus.h"

// void	ft_error(const char *msg)
// {
// 	ft_printf("%s", msg);
// 	exit(1);
// }

// void	ft_handler(int sig, siginfo_t *info, void *context)
// {
// 	static unsigned char	val = 0;
// 	static int				bit = 0;

// 	(void)context;
// 	val |= (sig == SIGUSR2) << bit++;
// 	if (bit == 8)
// 	{
// 		if (val == 0)
// 			kill(info->si_pid, SIGUSR2); // Bitiş sinyali gönder
// 		else
// 			ft_printf("%c", val);       // Karakteri yazdır
// 		val = bit = 0;
// 	}
// 	kill(info->si_pid, SIGUSR1);         // Onay sinyali gönder
// }

// int	main(void)
// {
// 	struct sigaction sa = {0};

// 	sa.sa_sigaction = ft_handler;
// 	sa.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
// 		ft_error("Signal Error\n");
// 	ft_printf("PID: %d\n", getpid());
// 	while (1)
// 		pause();
// }
