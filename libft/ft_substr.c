/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:20:30 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:20 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_allocempty(void)
{
	char	*out;

	out = ft_calloc(1, sizeof(unsigned char));
	if (out != NULL)
		out[0] = '\0';
	return (out);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*out;

	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_allocempty());
	if (len + start > s_len)
		len = s_len - start;
	if (*s == '\0')
	{
		out = (char *)ft_calloc(1, (sizeof (unsigned char)));
		out [0] = 0;
	}
	else
		out = (char *)ft_calloc(len + 1, (sizeof (unsigned char)));
	if (out != NULL && *s)
		ft_strlcpy(out, &s[start], len + 1);
	return (out);
}
