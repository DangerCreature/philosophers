/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:33:37 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:45:33 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	*ucs1;
	unsigned char	*ucs2;

	idx = 0;
	ucs1 = (unsigned char *)s1;
	ucs2 = (unsigned char *)s2;
	while (idx < n)
	{
		if (ucs1[idx] != ucs2[idx])
		{
			return (ucs1[idx] - ucs2[idx]);
		}
		idx++;
	}
	return (0);
}
