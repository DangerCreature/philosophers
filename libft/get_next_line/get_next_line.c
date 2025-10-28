/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:52:21 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/07 12:26:43 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		make_next_line(t_list *list, char *next_line, int next_line_len);
int		get_nl_idx(char *s);
int		fill_list(t_list *list, int fd);
void	free_used_list(t_list **list, int error);
int		make_list_entry(t_list *list, int fd);

char	*get_next_line(int fd)
{
	static t_list	*list;
	int				next_l_len;
	char			*next_line;

	if (!list)
	{
		list = (t_list *)malloc(sizeof (t_list));
		if (!list)
			return (NULL);
		list->next = NULL;
		list->str = NULL;
	}
	next_l_len = fill_list(list, fd);
	if (next_l_len > 0)
	{
		next_line = (char *)malloc(next_l_len + 1);
		if (next_line)
		{
			make_next_line(list, next_line, next_l_len);
			free_used_list(&list, 0);
			return (next_line);
		}
	}
	free_used_list(&list, 1);
	return (NULL);
}

int	make_list_entry(t_list *list, int fd)
{
	static char	buffer[BUFFER_SIZE];
	int			read_size;
	int			idx;

	idx = -1;
	if (!list->str)
	{
		if (fd < 0)
			return (-1);
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 1)
			return (read_size);
		list->str = (char *)malloc(read_size + 1);
		if (!list->str)
			return (-1);
		while (++idx < read_size)
			list->str[idx] = buffer[idx];
		list->str[read_size] = '\0';
		return (read_size);
	}
	return (ft_strlen(list->str));
}

int	fill_rest_of_list(t_list *list, int fd)
{
	int	next_l_len;
	int	read_size;
	int	nl_idx;

	nl_idx = get_nl_idx(list->str);
	next_l_len = nl_idx + 1;
	read_size = ft_strlen(list->str);
	while ((list->str[nl_idx] != '\n' && (read_size == nl_idx + 1)))
	{
		list->next = (t_list *)malloc(sizeof (t_list));
		if (!list->next)
			return (-1);
		list = list->next;
		list->next = NULL;
		list->str = NULL;
		read_size = make_list_entry(list, fd);
		if (read_size == -1)
			return (-1);
		nl_idx = get_nl_idx(list->str);
		next_l_len += nl_idx + 1;
		if (read_size < BUFFER_SIZE)
			break ;
	}
	return (next_l_len);
}

int	fill_list(t_list *list, int fd)
{
	int	next_l_len;
	int	read_size;

	if (!list->str)
	{
		read_size = make_list_entry(list, fd);
		if (read_size < 1)
			return (-1);
		if (read_size < BUFFER_SIZE)
			return (get_nl_idx(list->str) + 1);
	}
	next_l_len = fill_rest_of_list(list, fd);
	return (next_l_len);
}

int	make_next_line(t_list *list, char *next_line, int next_line_len)
{
	int		nextl_idx;
	int		this_entry_len;

	if (!list || !list->str || !next_line)
		return (0);
	nextl_idx = ft_strlcpy(next_line, list->str, next_line_len + 1);
	next_line_len -= nextl_idx;
	while (list->next && list->next->str)
	{
		list = list->next;
		this_entry_len = ft_strlcpy(&next_line[nextl_idx], 
				list->str, next_line_len + 1);
		next_line_len -= this_entry_len;
		nextl_idx += this_entry_len;
	}
	return (next_line_len);
}
