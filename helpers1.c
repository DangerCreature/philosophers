/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:05:06 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/28 11:52:48 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_isspace(unsigned char c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	safe_atoi(const char *nptr)
{
	long	out;
	int		sign;

	out = 0;
	sign = 1;
	if (!nptr)
		return (ERROR_NUM);
	while (ft_isspace((unsigned char)*nptr))
		nptr++;
	if ((unsigned char)*nptr == '-' || (unsigned char)*nptr == '+')
	{
		if ((unsigned char)*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) == 1)
	{
		out = (10 * out) + *nptr - '0';
		if (out < -2147483648)
			return (ERROR_NUM);
		nptr++;
	}
	if (*nptr || out * sign > 2147483647)
		return (ERROR_NUM);
	return ((int)(sign * out));
}
