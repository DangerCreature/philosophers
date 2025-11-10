/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabel_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:26:55 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/03 18:08:49 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	close_weltschmerz(t_tabel *tabelptr)
{
	if (tabelptr->weltschmerz_is_semed)
	{
		sem_close(tabelptr->weltschmerz);
		sem_unlink("/weltschmerz");
		tabelptr->weltschmerz_is_semed = 0;
	}
	if (tabelptr->weltschmerz_mutex_is_semed)
	{
		sem_close(tabelptr->weltschmerz_mutex);
		sem_unlink("/weltschmerz_mutex");
		tabelptr->weltschmerz_mutex_is_semed = 0;
	}
}

void	close_sems(t_tabel *tabelptr)
{
	if (tabelptr->num_forks_is_semed)
	{
		sem_close(tabelptr->sem_num_forks);
		sem_unlink("/sem_num_forks");
		tabelptr->num_forks_is_semed = 0;
	}
	if (tabelptr->fork_mutex_is_semed)
	{
		sem_close(tabelptr->fork_mutex);
		sem_unlink("/fork_mutex");
		tabelptr->fork_mutex_is_semed = 0;
	}
	if (tabelptr->write_is_semed)
	{
		sem_close(tabelptr->write_mutex);
		sem_unlink("/write_mutex");
		tabelptr->write_is_semed = 0;
	}
	close_weltschmerz(tabelptr);
}

void	tabel_clear_yourself(t_tabel *tabelptr)
{
	int	idx;

	idx = 0;
	if (tabelptr->pids_are_malloced)
	{
		while (idx < tabelptr->num_philos)
		{
			if (tabelptr->pids[idx] != -1)
			{
				waitpid(tabelptr->pids[idx], NULL, 0);
			}
			idx ++;
		}
		free(tabelptr->pids);
		tabelptr->pids_are_malloced = 0;
	}
	close_sems(tabelptr);
}
