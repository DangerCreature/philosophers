/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:52:40 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 11:14:59 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	destroy_other_mutexes(t_tabel *tabelptr)
{
	if (tabelptr->weltschmerz_is_mutexed)
		pthread_mutex_destroy(&tabelptr->weltschmerz_mutex);
	tabelptr->weltschmerz_is_mutexed = 0;
}

void	tabel_clear_yourself(t_tabel *tabelptr)
{
	int	idx;

	idx = 0;
	if (tabelptr->philos_are_malleoced)
	{
		while (idx < tabelptr->num_philos)
		{
			if (tabelptr->philos[idx].is_threaded)
				pthread_join(tabelptr->philos[idx].thread, NULL);
			idx ++;
		}
		free(tabelptr->philos);
		tabelptr->philos_are_malleoced = 0;
	}
	if (!tabelptr->forks_is_malloced)
		return ;
	while (idx < tabelptr->pt_m_num)
		pthread_mutex_destroy(&tabelptr->forks[idx++].mutex);
	free(tabelptr->forks);
	tabelptr->forks_is_malloced = 0;
	if (tabelptr->write_is_mutexed)
		pthread_mutex_destroy(&tabelptr->write_mutex);
	tabelptr->write_is_mutexed = 0;
	destroy_other_mutexes(tabelptr);
}
