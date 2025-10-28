/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:57:16 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:45:52 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	size_t			idx;
	unsigned char	*s_uchar;

	idx = 0;
	s_uchar = (unsigned char *)s;
	while (idx < len)
	{
		s_uchar[idx] = (unsigned char)c;
		idx++;
	}
	return (s);
}
