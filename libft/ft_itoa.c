/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:16:38 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 11:03:30 by gwolfrum         ###   ########.fr       */
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

char	*ft_itoa(int n)
{
	char	pre[13];
	int		idx;

	idx = 11;
	pre[12] = '\0';
	pre[0] = ' ';
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
	return (ft_strdup(&pre[idx + 1]));
}
