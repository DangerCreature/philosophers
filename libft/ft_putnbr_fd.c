/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:18:15 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:45:59 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	char	pre[13];
	int		idx;

	idx = 11;
	pre[12] = '\0';
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
	ft_putstr_fd(&pre[idx + 1], fd);
}
