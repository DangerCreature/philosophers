/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:00:25 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:45:31 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*heystack;
	unsigned char	needle;
	size_t			idx;

	heystack = (unsigned char *)s;
	needle = (unsigned char)c;
	idx = 0;
	if (n == 0)
		return (NULL);
	while (heystack[idx] != needle && idx + 1 < n)
	{
		idx++;
	}
	if (heystack[idx] == needle)
	{
		return ((void *)&heystack[idx]);
	}
	return (NULL);
}
