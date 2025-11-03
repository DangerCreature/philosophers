/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:04:29 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/03 18:03:05 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	let_go_of_fork(t_philo philo, t_tabel tabel);
int	try_grabbing_forks(t_philo *philoptr, t_tabel tabel);

int	check_death(t_philo philo, t_tabel tabel)
{
	if (weltschmerz_is(&philo, tabel) != 0)
		chiald_die(philo);
	if (now() - philo.last_meal > tabel.time_to_die)
	{
		sem_post(tabel.weltschmerz);
		status_update(philo, DIED, NULL);
		chiald_die(philo);
	}
	return (0);
}

int	try_eating(t_philo *philoptr, t_tabel tabel)
{
	long	start_eat;

	check_death(*philoptr, tabel);
	if (philoptr->activity != EATING)
		return (1);
	start_eat = now();
	status_update(*philoptr, EATING, NULL);
	while ((now() - start_eat) < tabel.time_to_eat)
	{
		usleep(300);
	}
	check_death(*philoptr, tabel);
	let_go_of_fork(*philoptr, tabel);
	let_go_of_fork(*philoptr, tabel);
	philoptr->last_meal = now();
	philoptr->num_meals ++;
	philoptr->activity = -1;
	return (0);
}

int	try_sleeping(t_philo *philoptr, t_tabel tabel)
{
	long	start_sleep;

	check_death(*philoptr, tabel);
	if (philoptr->last_meal < philoptr->last_sleep)
		return (1);
	start_sleep = now();
	status_update(*philoptr, SLEEPING, NULL);
	while ((now() - start_sleep) < tabel.time_to_sleep)
	{
		usleep(300);
	}
	check_death(*philoptr, tabel);
	philoptr->last_sleep = now();
	philoptr->activity = -1;
	return (0);
}

int	try_thinking(t_philo *philoptr, t_tabel tabel)
{
	check_death(*philoptr, tabel);
	if (philoptr->activity == -1)
	{
		status_update(*philoptr, THINKING, NULL);
		philoptr->activity = THINKING;
	}
	return (0);
}

void	rutine(t_philo *philoptr)
{
	t_tabel	tabel;

	tabel = *philoptr->tabelptr;
	while (!weltschmerz_is(philoptr, tabel))
	{
		try_grabbing_forks(philoptr, tabel);
		try_eating(philoptr, tabel);
		try_sleeping(philoptr, tabel);
		try_thinking(philoptr, tabel);
		check_death(*philoptr, tabel);
		usleep(500);
	}
	chiald_die(*philoptr);
}
