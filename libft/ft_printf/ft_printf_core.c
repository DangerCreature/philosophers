/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:00:19 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/05 11:33:37 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	put_tnf_error(char c)
{
	ft_printf("ERROR: '%c' - type not found", (int)c);
	return (-1);
}

static int	put_var(const char *s, va_list *args)
{
	if (s[1] == 'c')
		return ((int)ft_putchr ((int)va_arg(*args, int)));
	if (s[1] == '%')
		return ((int)ft_putchr('%'));
	if (s[1] == 's')
		return ((int)ft_putstr((char *)va_arg(*args, char *)));
	if (s[1] == 'd')
		return ((int)ft_putnbr((int)va_arg(*args, int)));
	if (s[1] == 'i')
		return ((int)ft_putnbr((int)va_arg(*args, int)));
	if (s[1] == 'x')
		return ((int)ft_putnbr_base((long) va_arg(*args, unsigned int)
				, "0123456789abcdef"));
	if (s[1] == 'X')
		return ((int)ft_putnbr_base((long) va_arg(*args, unsigned int)
				, "0123456789ABCDEF"));
	if (s[1] == 'u')
		return ((int)ft_putnbr_base((long) va_arg(*args, unsigned int)
				, "0123456789"));
	if (s[1] == 'p')
		return ((int)ft_putadress((unsigned long long) va_arg(*args, void *)
				, "0123456789abcdef"));
	return (put_tnf_error(s[1]));
}

int	ft_printf(const char *s, ...)
{
	int		write_len;
	int		cur_write_len;
	va_list	args;

	write_len = 0;
	cur_write_len = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			cur_write_len = put_var(s++, &args);
		}
		else 
			cur_write_len = (int)write(1, s, 1);
		if (cur_write_len == -1)
			return (-1);
		write_len += cur_write_len;
		s ++;
	}
	va_end(args);
	return (write_len);
}
