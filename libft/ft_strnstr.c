/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:52:01 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 10:02:33 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	idx;

	idx = 0;
	len_little = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	if (big == NULL)
		*((volatile int *) NULL) = 1;
	while (idx + len_little <= len && big[idx] != 0)
	{
		if (ft_strncmp(&big[idx], little, len_little) == 0)
			return ((char *)&big[idx]);
		idx++;
	}
	return (NULL);
}
