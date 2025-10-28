/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:04:32 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 15:44:08 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putadress(unsigned long long nbr, char *base)
{
	int		base_len;
	int		idx_a;
	char	arr[132];

	base_len = (int) ft_strlen(base);
	idx_a = 131;
	if (nbr == 0)
		return ((int)ft_putstr("(nil)"));
	while (nbr > 0)
	{
		arr[idx_a] = base[nbr % base_len];
		nbr /= base_len;
		idx_a --;
	}
	arr [idx_a --] = 'x';
	arr [idx_a --] = '0'; 
	return ((int) write(1, &arr[idx_a + 1], 131 - idx_a));
}
