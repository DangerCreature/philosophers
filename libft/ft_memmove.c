/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:06:24 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 10:36:36 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memmove_helper(unsigned char *dest, unsigned char *src
	, size_t n)
{
	size_t	idx;

	if (dest < src)
	{
		idx = 0;
		while (idx < n)
		{
			dest[idx] = src[idx];
			idx++;
		}
	}
	else if (dest > src)
	{
		idx = n;
		while (idx > 0)
		{
			dest[idx - 1] = src[idx - 1];
			idx--;
		}
	}
	else
	{
		return ;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	ft_memmove_helper((unsigned char *)dest, (unsigned char *)src, n);
	return (dest);
}
