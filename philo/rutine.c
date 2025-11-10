/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:29:19 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/10 10:26:22 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	try_grabbing_forks(t_philo *philo_ptr);

int	check_death(t_philo philo)
{
	if (weltschmerz_is(philo.tabel))
		return (1);
	if (now() - philo.last_meal > philo.tabel->time_to_die)
	{
		set_weltschmerz(philo.tabel);
		status_update(philo, DIED);
		return (1);
	}
	return (0);
}

int	try_eating(t_philo *philo_ptr)
{
	long	start_eat;

	if (philo_ptr->activity != EATING || weltschmerz_is(philo_ptr->tabel))
		return (1);
	start_eat = now();
	status_update(*philo_ptr, EATING);
	while ((now() - start_eat)
		< philo_ptr->tabel->time_to_eat
		&& !weltschmerz_is(philo_ptr->tabel))
	{
		usleep(100);
	}
	if (weltschmerz_is(philo_ptr->tabel))
		return (1);
	let_go_of_fork(philo_ptr->right_fork, *philo_ptr);
	let_go_of_fork(philo_ptr->left_fork, *philo_ptr);
	philo_ptr->last_meal = now();
	philo_ptr->num_meals ++;
	philo_ptr->activity = -1;
	return (0);
}

int	try_sleeping(t_philo *philo_ptr)
{
	long	start_sleep;

	if (philo_ptr->last_meal < philo_ptr->last_sleep
		|| weltschmerz_is(philo_ptr->tabel))
		return (1);
	start_sleep = now();
	status_update(*philo_ptr, SLEEPING);
	while ((now() - start_sleep)
		< philo_ptr->tabel->time_to_sleep
		&& !weltschmerz_is(philo_ptr->tabel))
	{
		usleep(500);
		check_death(*philo_ptr);
	}
	philo_ptr->last_sleep = now();
	philo_ptr->activity = -1;
	return (0);
}

int	try_thinking(t_philo *philo_ptr)
{
	if (philo_ptr->activity == -1 && !weltschmerz_is(philo_ptr->tabel))
	{
		status_update(*philo_ptr, THINKING);
		philo_ptr->activity = THINKING;
	}
	return (0);
}

void	*rutine(void *args)
{
	t_philo	*philo_ptr;

	philo_ptr = (t_philo *)args;
	while (!weltschmerz_is(philo_ptr->tabel))
	{
		try_grabbing_forks(philo_ptr);
		try_eating(philo_ptr);
		if (philo_ptr->tabel->times_each_philo_needs_eat != -1
			&& philo_ptr->num_meals
			>= philo_ptr->tabel->times_each_philo_needs_eat)
		{
			return (args);
		}
		check_death(*philo_ptr);
		try_sleeping(philo_ptr);
		check_death(*philo_ptr);
		try_thinking(philo_ptr);
		check_death(*philo_ptr);
		usleep(200);
	}
	return (args);
}
