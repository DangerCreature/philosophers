/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:50:38 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:02 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*heystack;
	unsigned char	needle;

	heystack = (char *)s;
	needle = (unsigned char)c;
	while (*heystack != needle && *heystack)
	{
		heystack++;
	}
	if (*heystack == needle)
	{
		return (heystack);
	}
	return (NULL);
}
