/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_chiald.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 14:46:52 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/03 12:08:31 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

t_philo	birth(t_tabel *tabelptr)
{
	t_philo	baby;

	baby.time = now();
	baby.last_meal = baby.time;
	baby.last_sleep = baby.time;
	baby.num_meals = 0;
	baby.activity = -1;
	baby.tabelptr = tabelptr;
	baby.idx = 0;
	return (baby);
}

void	chiald_disconect_frem_world(t_tabel *tabelptr)
{
	if (tabelptr->num_forks_is_semed)
	{
		sem_close(tabelptr->sem_num_forks);
		tabelptr->num_forks_is_semed = 0;
	}
	if (tabelptr->fork_mutex_is_semed)
	{
		sem_close(tabelptr->fork_mutex);
		tabelptr->fork_mutex_is_semed = 0;
	}
	if (tabelptr->write_is_semed)
	{
		sem_close(tabelptr->write_mutex);
		tabelptr->write_is_semed = 0;
	}
	if (tabelptr->weltschmerz_is_semed)
	{
		sem_close(tabelptr->weltschmerz);
		tabelptr->weltschmerz_is_semed = 0;
	}
	if (tabelptr->weltschmerz_mutex_is_semed)
	{
		sem_close(tabelptr->weltschmerz_mutex);
		tabelptr->weltschmerz_mutex_is_semed = 0;
	}
}

void	chiald_die(t_philo philo)
{
	if (philo.tabelptr->pids_are_malloced)
	{
		free(philo.tabelptr->pids);
		philo.tabelptr->pids_are_malloced = 0;
	}
	chiald_disconect_frem_world(philo.tabelptr);
	exit (0);
}

