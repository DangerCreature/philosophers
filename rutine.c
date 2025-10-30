/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:29:19 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/30 17:31:54 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	try_grabbing_forks(t_philo *philo_ptr);

int	check_death(t_philo philo)
{
	if (philo.tabel->weltschmerz)
		return (1);
	if (philo.tabel->now - philo.last_meal > philo.tabel->time_to_die)
	{
		philo.tabel->weltschmerz = 1;
		status_update(philo, DIED);
		return (1);
	}
	return (0);
}

int	try_eating(t_philo *philo_ptr)
{
	long	start_eat;

	if (philo_ptr->activity != EATING || philo_ptr->tabel->weltschmerz)
		return (1);
	start_eat = philo_ptr->tabel->now;
	status_update(*philo_ptr, EATING);
	while ((philo_ptr->tabel->now - start_eat)
		< philo_ptr->tabel->time_to_eat
		&& philo_ptr->tabel->weltschmerz == 0)
	{
		usleep(100);
	}
	if (philo_ptr->tabel->weltschmerz)
		return (1);
	let_go_of_fork(philo_ptr->right_fork, *philo_ptr);
	let_go_of_fork(philo_ptr->left_fork, *philo_ptr);
	philo_ptr->last_meal = philo_ptr->tabel->now;
	philo_ptr->num_meals ++;
	philo_ptr->activity = -1;
	return (0);
}

int	try_sleeping(t_philo *philo_ptr)
{
	long	start_sleep;

	if (philo_ptr->last_meal < philo_ptr->last_sleep
		|| philo_ptr->tabel->weltschmerz)
		return (1);
	start_sleep = philo_ptr->tabel->now;
	status_update(*philo_ptr, SLEEPING);
	while ((philo_ptr->tabel->now - start_sleep)
		< philo_ptr->tabel->time_to_sleep
		&& philo_ptr->tabel->weltschmerz == 0)
	{
		usleep(500);
		check_death(*philo_ptr);
	}
	philo_ptr->last_sleep = philo_ptr->tabel->now;
	philo_ptr->activity = -1;
	return (0);
}

int	try_thinking(t_philo *philo_ptr)
{
	if (philo_ptr->activity == -1 && !philo_ptr->tabel->weltschmerz)
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
	while (philo_ptr->tabel->weltschmerz == 0)
	{
		try_grabbing_forks(philo_ptr);
		try_eating(philo_ptr);
		check_death(*philo_ptr);
		try_sleeping(philo_ptr);
		check_death(*philo_ptr);
		try_thinking(philo_ptr);
		check_death(*philo_ptr);
		usleep(200);
	}
	return (args);
}
