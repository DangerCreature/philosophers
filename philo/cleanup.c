/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:52:40 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/30 16:29:42 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	tabel_clear_yourself(t_tabel *tabel)
{
	int	idx;

	idx = 0;
	if (tabel->philos_are_malleoced)
	{
		while (idx < tabel->num_philos)
		{
			if (tabel->philos[idx].is_threaded)
				pthread_join(tabel->philos[idx].thread, NULL);
			idx ++;
		}
		free(tabel->philos);
		tabel->philos_are_malleoced = 0;
	}
	if (!tabel->forks_is_malloced)
		return ;
	while (idx < tabel->pt_m_num)
		pthread_mutex_destroy(&tabel->forks[idx++].mutex);
	free(tabel->forks);
	tabel->forks_is_malloced = 0;
	if (tabel->write_is_mutexed)
		pthread_mutex_destroy(&tabel->write_mutex);
	tabel->write_is_mutexed = 0;
}
