/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:02:21 by malbayra          #+#    #+#             */
/*   Updated: 2025/01/29 20:34:50 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void    ft_handler(int sig, siginfo_t *info, void *context)
{
    static unsigned char c = 0;
    static int           bit = 0;
    (void)context; // kullanılmıyor
    // SIGUSR2 geldiyse bit=1, SIGUSR1 geldiyse bit=0 (tam tersi de mümkün, yeter ki istemciyle uyumlu olsun)
    if (sig == SIGUSR2)
        c |= (1 << bit);
    bit++;
    // 8 bit toplandıysa, elimizde tamamlanmış 1 bayt var
    if (bit == 8)
    {
        if (c == '\0')
        {
            // Null terminatör => mesajın sonu
            // İstemciye "bitti" anlamında SIGUSR2 gönderiyoruz
            kill(info->si_pid, SIGUSR2);
        }
        else
        {
            // Alınan baytı ekrana yaz
            write(1, &c, 1);
            // İstemciye bir sonraki baytı göndermesi için SIGUSR1 gönder
            kill(info->si_pid, SIGUSR1);
        }
        // Bir sonraki bayt için sıfırla
        c = 0;
        bit = 0;
        return ;
    }
    else
    {
        // Henüz 1 bayt tamamlanmadı; istemciye "devam" sinyali gönder
        kill(info->si_pid, SIGUSR1);
    }
}
int main(void)
{
    struct sigaction sa;
    sa.sa_sigaction = &ft_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        printf("Signal Error\n");
        return (1);
    }
    printf("Sunucu PID: %d\n", getpid());
    while (1)
        pause();
    return (0);
}


