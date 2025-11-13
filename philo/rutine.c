/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rutine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:29:19 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/12 15:23:00 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	try_grabbing_forks(t_philo *philo_ptr);

int	check_death(t_philo *philo_ptr)
{
	if (weltschmerz_is(philo_ptr->tabel))
		return (1);
	if (now() - philo_ptr->last_meal >= philo_ptr->tabel->time_to_die)
	{
		status_update(*philo_ptr, DIED);
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
	philo_ptr->last_meal = start_eat;
	while ((now() - start_eat)
		< philo_ptr->tabel->time_to_eat
		&& !weltschmerz_is(philo_ptr->tabel))
	{
		usleep(100);
	}
	pthread_mutex_unlock(&philo_ptr->left_fork->mutex);
	pthread_mutex_unlock(&philo_ptr->right_fork->mutex);
	philo_ptr->activity = -2;
	if (weltschmerz_is(philo_ptr->tabel))
		return (1);
	philo_ptr->num_meals ++;
	return (0);
}

int	try_sleeping(t_philo *philo_ptr)
{
	long	start_sleep;

	if (weltschmerz_is(philo_ptr->tabel))
		return (1);
	start_sleep = now();
	status_update(*philo_ptr, SLEEPING);
	while ((now() - start_sleep)
		< philo_ptr->tabel->time_to_sleep
		&& !weltschmerz_is(philo_ptr->tabel))
	{
		usleep(500);
		check_death(philo_ptr);
	}
	philo_ptr->activity = -1;
	return (0);
}

int	try_thinking(t_philo *philo_ptr)
{
	if (philo_ptr->activity == -1 && !weltschmerz_is(philo_ptr->tabel))
	{
		status_update(*philo_ptr, THINKING);
		philo_ptr->activity = THINKING;
		check_death(philo_ptr);
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
			break ;
		check_death(philo_ptr);
		try_sleeping(philo_ptr);
		check_death(philo_ptr);
		try_thinking(philo_ptr);
		usleep(200);
	}
	if (philo_ptr->activity == EATING)
	{
		pthread_mutex_unlock(&philo_ptr->left_fork->mutex);
		status_update(*philo_ptr, FORK_RETURN);
		pthread_mutex_unlock(&philo_ptr->right_fork->mutex);
		status_update(*philo_ptr, FORK_RETURN);
	}
	return (args);
}
