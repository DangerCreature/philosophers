/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:13:35 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 19:06:34 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	strlen;

	if (!s)
		return (ft_putstr("(null)"));
	strlen = 0;
	while (s[strlen])
		strlen ++;
	return ((int)write(1, s, strlen));
}

int	ft_putchr(int c)
{
	return ((int)write(1, &c, 1));
}
