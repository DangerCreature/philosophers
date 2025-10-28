/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:39:23 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/09/24 10:20:48 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	make_rest(t_list *temp);

int	get_nl_idx(char *s)
{
	int	nl_idx;

	if (!s)
		return (-1);
	nl_idx = 0;
	while (s[nl_idx] && s[nl_idx] != '\n')
		nl_idx ++;
	if (!s[nl_idx])
		nl_idx --;
	return (nl_idx);
}

void	free_used_list(t_list **list, int error)
{
	t_list	*temp;

	while ((*list)->next)
	{
		temp = *list;
		*list = (*list)->next;
		if (temp->str)
			free (temp->str);
		free (temp);
	}
	temp = *list;
	if (temp->str && error == 0)
	{
		make_rest(temp);
		return ;
	}
	if (temp->str)
		free(temp->str);
	free(temp);
	*list = NULL;
}

void	make_rest(t_list *temp)
{
	char	*rest;
	int		nl_idx;
	int		rest_len;

	nl_idx = get_nl_idx(temp->str);
	rest_len = (int)ft_strlen(temp->str) - (nl_idx + 1);
	if (rest_len > 0)
	{
		rest = malloc(rest_len + 1);
		if (rest)
			ft_strlcpy(rest, &temp->str[nl_idx + 1], rest_len + 1);
	}
	else
		rest = NULL;
	free(temp->str);
	temp->str = rest;
}
