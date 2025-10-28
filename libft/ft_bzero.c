/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:44:57 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:44:34 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			idx;
	unsigned char	*s_uchar;

	idx = 0;
	s_uchar = (unsigned char *)s;
	while (idx < n)
	{
		s_uchar[idx] = (unsigned char) '\0';
		idx++;
	}
}
