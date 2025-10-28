/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:54:42 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:08 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	char			*s_out;

	idx = 0;
	s_out = (char *)ft_calloc(ft_strlen(s) + 1, sizeof (char));
	if (s_out != NULL)
	{
		while (s[idx])
		{
			s_out[idx] = f(idx, s[idx]);
			idx++;
		}
		s_out[idx] = '\0';
	}
	return (s_out);
}
