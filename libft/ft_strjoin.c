/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:47:39 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:05 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	out_len;
	size_t	s1_len;
	size_t	s2_len;
	char	*out;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out_len = s1_len + s2_len;
	out = (char *)ft_calloc(out_len + 1, (sizeof (char)));
	if (out == NULL)
		return (out);
	ft_strlcpy(out, s1, s1_len + 1);
	ft_strlcpy(out + s1_len, s2, s2_len + 1);
	return (out);
}
