/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:53:24 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:03 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*out;

	len = ft_strlen(s) + 1;
	out = (char *)ft_calloc(len, sizeof (char));
	if (out == NULL)
		return (NULL);
	ft_strlcpy (out, s, len);
	return (out);
}
