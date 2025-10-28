/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:40:31 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 11:04:10 by gwolfrum         ###   ########.fr       */
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

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s2_start;
	size_t	s2_end;
	char	*out;

	s2_start = 0;
	s2_end = ft_strlen(s1);
	if (s2_end == 0)
		return (ft_allocempty());
	s2_end --;
	while (ft_strchr(set, s1[s2_start]) != NULL)
		s2_start++;
	while (ft_strchr(set, s1[s2_end]) != NULL && s2_end >= s2_start)
		s2_end--;
	if (s2_start > s2_end)
		return (ft_allocempty());
	out = (char *)ft_calloc(s2_end - s2_start + 2, sizeof (char));
	if (out == NULL)
		return (NULL);
	ft_strlcpy (out, s1 + s2_start, s2_end - s2_start + 2);
	return (out);
}
