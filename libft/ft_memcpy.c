/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:33:14 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:45:40 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				idx;
	unsigned char		*dest_uchar;
	const unsigned char	*src_uchar;

	idx = 0;
	dest_uchar = (unsigned char *)dest;
	src_uchar = (const unsigned char *)src;
	if ((dest == NULL && src == NULL))
		return (NULL);
	while (idx < n)
	{
		dest_uchar[idx] = src_uchar[idx];
		idx++;
	}
	return (dest);
}
