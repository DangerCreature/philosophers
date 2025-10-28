/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:04:32 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 19:20:54 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(long nbr, char *base)
{
	int		idx_a;
	char	arr[32];
	int		base_len;

	base_len = ft_strlen(base);
	idx_a = 31;
	arr[0] = ' ';
	if (nbr == 0)
	{
		return (write(1, &base[0], 1));
	}
	if (nbr > 0)
		nbr *= -1;
	else
		arr[0] = '-';
	while (nbr < 0)
	{
		arr[idx_a--] = base[-nbr % base_len];
		nbr /= base_len;
	}
	if (arr[0] == '-')
		arr[idx_a--] = '-';
	return ((int) write(1, &arr[idx_a + 1], 31 - idx_a));
}
