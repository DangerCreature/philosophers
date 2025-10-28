/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:13:24 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 17:29:17 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_arr(char *pre, int n, int *idx)
{
	while (n < 0)
	{
		pre[*idx] = '0' - (n % 10);
		n /= 10;
		(*idx)--;
	}
	if (pre[0] == '-')
	{
		pre[*idx] = '-';
		(*idx)--;
	}
}

int	ft_putnbr(int n)
{
	char	pre[13];
	int		idx;

	idx = 11;
	pre[12] = '\0';
	pre[0] = '\0';
	if (n > 0)
		n *= -1;
	else if (n == 0)
	{
		pre[idx] = '0';
		idx--;
	}
	else
		pre[0] = '-';
	fill_arr(pre, n, &idx);
	return (ft_putstr(&pre[idx + 1]));
}
