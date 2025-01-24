/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbayra <malbayra@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:56:40 by malbayra          #+#    #+#             */
/*   Updated: 2024/11/09 14:58:19 by malbayra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check(char c, va_list arg)
{
	unsigned long	p;

	if (c == 'c')
		return (ft_putchar(va_arg(arg, int)));
	if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(arg, int)));
	if (c == 'u')
		return (ft_u(va_arg(arg, unsigned int)));
	if (c == 'x')
		return (ft_hex(va_arg(arg, unsigned int), 0));
	if (c == 'X')
		return (ft_hex(va_arg(arg, unsigned int), 1));
	if (c == 'p')
	{
		p = va_arg(arg, unsigned long);
		if (p == 0)
			return (ft_putstr("(nil)"));
		return (ft_putstr("0x") + ft_pointer(p));
	}
	if (c == '%')
		return (ft_putchar('%'));
	ft_putchar('%');
	return (ft_putchar(c));
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		i;
	int		check;

	va_start(arg, str);
	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar(str[i]);
			check++;
		}
		if (str[i] == '%')
		{
			i++;
			while (str[i] == ' ' && str[i])
				i++;
			check += ft_check(str[i], arg);
		}
		i++;
	}
	va_end(arg);
	return (check);
}
