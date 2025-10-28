/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:22:30 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:14 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*heystack;
	unsigned char	needle;
	size_t			idx;

	heystack = (char *)s;
	needle = (unsigned char)c;
	idx = ft_strlen(s);
	while (heystack[idx] != needle && idx > 0)
	{
		idx--;
	}
	if (heystack[idx] == needle)
	{
		return (&heystack[idx]);
	}
	return (NULL);
}
