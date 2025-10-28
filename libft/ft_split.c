/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:57:30 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/06/04 09:46:01 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_substr_count(const char *s, char c)
{
	size_t	accr;
	int		is_c;

	is_c = 1;
	accr = 0;
	while (*s)
	{
		if ((*s != c) && is_c == 1)
		{
			accr++;
			is_c = 0;
		}
		else if (*s == c)
		{
			is_c = 1;
		}
		s++;
	}
	return (accr);
}

static size_t	ft_str_idx_chr(const char *s, char c)
{
	size_t	idx;

	idx = 0;
	while (s[idx] && s[idx] != c)
	{
		idx++;
	}
	return (idx);
}

static char	**ft_rec_free(char **out_arr, int entry_count)
{
	int	idx;

	idx = 0;
	if (!out_arr)
		return (NULL);
	while (idx < entry_count)
	{
		free(out_arr[idx]);
		idx++;
	}
	free(out_arr);
	return (NULL);
}

static char	**ft_fill_arr(char const *s, char c, char **out_arr, int num_entrys)
{
	size_t	this_entry_len;
	size_t	idx;
	int		entry_count;

	this_entry_len = 0;
	idx = 0;
	entry_count = 0;
	out_arr[num_entrys - 1] = NULL;
	while (entry_count < num_entrys - 1)
	{
		this_entry_len = ft_str_idx_chr(&s[idx], c);
		if (this_entry_len > 0)
		{
			out_arr[entry_count] = ft_substr(s, idx, this_entry_len);
			if (out_arr[entry_count] == NULL)
				return (ft_rec_free(out_arr, entry_count));
			entry_count++;
		}
		idx += this_entry_len + 1;
	}
	return (out_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**out_arr;
	int		entry_count;

	entry_count = ft_substr_count(s, c) + 1;
	if (s == NULL)
		return (NULL);
	out_arr = (char **)ft_calloc(entry_count, sizeof(char *));
	if (out_arr == NULL)
		return (NULL);
	return (ft_fill_arr(s, c, out_arr, entry_count));
}
