/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:21:21 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/13 10:30:08 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	will_i_survive_the_wait(t_philo *philo_ptr)
{
	t_tabel	*tabel;

	tabel = philo_ptr->tabel;
	if ((now() - tabel->time) / tabel->time_to_eat < 2 + tabel->num_philos % 2)
	{
		if (tabel->num_philos % 2 && philo_ptr->idx == 0)
			return (2 * tabel->time_to_eat <= tabel->time_to_die);
		if (philo_ptr->idx % 2 == 0)
			return (tabel->time_to_eat <= tabel->time_to_die);
		return (tabel->time_to_die);
	}
	if (tabel->num_philos % 2 == 0)
	{
		if (tabel->time_to_eat < tabel->time_to_sleep)
			return (tabel->time_to_eat + tabel->time_to_sleep
				<= tabel->time_to_die);
		return (2 * tabel->time_to_eat <= tabel->time_to_die);
	}
	else
	{
		if (tabel->time_to_eat * 2 < tabel->time_to_sleep)
			return (tabel->time_to_eat + tabel->time_to_sleep
				<= tabel->time_to_die);
		return (3 * tabel->time_to_eat <= tabel->time_to_die);
	}
}

void	wait_to_die(t_philo *philo_ptr)
{
	while (!weltschmerz_is(philo_ptr->tabel))
	{
		check_death(philo_ptr);
		usleep(500);
	}
}

void	grep_left_fork_first(t_philo *philo_ptr)
{
	pthread_mutex_lock(&philo_ptr->left_fork->mutex);
	if (weltschmerz_is(philo_ptr->tabel))
	{
		pthread_mutex_unlock(&philo_ptr->left_fork->mutex);
		return ;
	}
	status_update(*philo_ptr, FORK_GRAB);
	pthread_mutex_lock(&philo_ptr->right_fork->mutex);
	if (weltschmerz_is(philo_ptr->tabel))
	{
		pthread_mutex_unlock(&philo_ptr->left_fork->mutex);
		pthread_mutex_unlock(&philo_ptr->right_fork->mutex);
		return ;
	}
	philo_ptr->activity = EATING;
	status_update(*philo_ptr, FORK_GRAB);
}

void	grep_right_fork_first(t_philo *philo_ptr)
{
	pthread_mutex_lock(&philo_ptr->right_fork->mutex);
	if (weltschmerz_is(philo_ptr->tabel))
	{
		pthread_mutex_unlock(&philo_ptr->right_fork->mutex);
		return ;
	}
	status_update(*philo_ptr, FORK_GRAB);
	pthread_mutex_lock(&philo_ptr->left_fork->mutex);
	if (weltschmerz_is(philo_ptr->tabel))
	{
		pthread_mutex_unlock(&philo_ptr->left_fork->mutex);
		pthread_mutex_unlock(&philo_ptr->right_fork->mutex);
		return ;
	}
	philo_ptr->activity = EATING;
	status_update(*philo_ptr, FORK_GRAB);
}

int	try_grabbing_forks(t_philo *philo_ptr)
{
	if (!will_i_survive_the_wait(philo_ptr)
		|| philo_ptr->tabel->num_philos == 1)
	{
		wait_to_die(philo_ptr);
		return (1);
	}
	if (now() - philo_ptr->last_meal < philo_ptr->tabel->time_to_sleep + 1
		&& philo_ptr->num_meals != 0)
		usleep (100);
	if (philo_ptr->idx == 0 || !(philo_ptr->idx % 2))
		grep_left_fork_first(philo_ptr);
	else
	{
		if (((now() - philo_ptr->tabel->time) / philo_ptr->tabel->time_to_eat)
			< 2 + philo_ptr->tabel->num_philos % 2)
		{
			if (philo_ptr->idx == 0 && philo_ptr->tabel->num_philos % 2)
				usleep(1000);
			usleep(4000);
		}
		grep_right_fork_first(philo_ptr);
	}
	return (0);
}
