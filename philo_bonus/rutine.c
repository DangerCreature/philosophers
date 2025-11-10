/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:04:29 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 11:02:38 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	let_go_of_fork(t_philo philo, t_tabel tabel);
int	try_grabbing_forks(t_philo *philoptr, t_tabel tabel);

int	check_death(t_philo philo, t_tabel tabel)
{
	if (weltschmerz_is(&philo, tabel)
		|| (philo.num_meals >= tabel.number_each_philo_needs_eat
			&& tabel.number_each_philo_needs_eat != -1))
	{
		chiald_die(philo);
	}
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

	if (philoptr->num_meals != 0
		&& now() - philoptr->last_meal < tabel.time_to_sleep + 5)
		usleep(700);
	try_grabbing_forks(philoptr, tabel);
	if (philoptr->activity != EATING)
		return (1);
	start_eat = clean_now(philoptr, tabel);
	philoptr->last_meal = start_eat;
	check_death(*philoptr, tabel);
	status_update(*philoptr, EATING, NULL);
	while ((now() - start_eat) < tabel.time_to_eat)
	{
		check_death(*philoptr, tabel);
	}
	philoptr->last_meal = now();
	let_go_of_fork(*philoptr, tabel);
	let_go_of_fork(*philoptr, tabel);
	philoptr->num_meals ++;
	philoptr->activity = -1;
	return (0);
}

int	try_sleeping(t_philo *philoptr, t_tabel tabel)
{
	long	start_sleep;

	check_death(*philoptr, tabel);
	if (philoptr->last_meal + 4 < philoptr->last_sleep)
		return (1);
	start_sleep = clean_now(philoptr, tabel);
	status_update(*philoptr, SLEEPING, NULL);
	while ((now() - start_sleep) < tabel.time_to_sleep)
	{
		check_death(*philoptr, tabel);
	}
	philoptr->last_sleep = now();
	philoptr->activity = -1;
	return (0);
}

int	try_thinking(t_philo *philoptr, t_tabel tabel)
{
	if (philoptr->activity == -1)
	{
		check_death(*philoptr, tabel);
		status_update(*philoptr, THINKING, NULL);
		philoptr->activity = THINKING;
	}
	return (0);
}

void	rutine(t_philo *philoptr)
{
	t_tabel	tabel;

	tabel = *philoptr->tabelptr;
	while (1)
	{
		check_death(*philoptr, tabel);
		try_eating(philoptr, tabel);
		try_sleeping(philoptr, tabel);
		try_thinking(philoptr, tabel);
	}
}
