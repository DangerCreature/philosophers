/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 09:21:21 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/30 16:51:28 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	grep_fork(t_fork *fork_ptr, t_philo philo)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&fork_ptr->mutex);
	if (fork_ptr->fork)
		fork_ptr->fork = 0;
	else
		out = 1;
	pthread_mutex_unlock(&fork_ptr->mutex);
	if (!out)
		status_update(philo, FORK_GRAB);
	return (out);
}

int	let_go_of_fork(t_fork *fork_ptr, t_philo philo)
{
	int	out;

	out = 0;
	pthread_mutex_lock(&fork_ptr->mutex);
	if (!fork_ptr->fork)
		fork_ptr->fork = 1;
	else
		out = 1;
	pthread_mutex_unlock(&fork_ptr->mutex);
	if (!out)
		status_update(philo, FORK_RETURN);
	return (out);
}

int	grep_left_fork_first(t_philo *philo_ptr)
{
	if (grep_fork(philo_ptr->left_fork, *philo_ptr) == 0)
	{
		if (grep_fork(philo_ptr->right_fork, *philo_ptr))
		{
			let_go_of_fork(philo_ptr->left_fork, *philo_ptr);
			return (1);
		}
		philo_ptr->activity = EATING;
	}
	else
		return (1);
	return (0);
}

int	grep_right_fork_first(t_philo *philo_ptr)
{
	if (grep_fork(philo_ptr->right_fork, *philo_ptr) == 0)
	{
		if (grep_fork(philo_ptr->left_fork, *philo_ptr))
		{
			let_go_of_fork(philo_ptr->right_fork, *philo_ptr);
			return (1);
		}
		philo_ptr->activity = EATING;
		philo_ptr->last_meal = philo_ptr->tabel->now;
	}
	else
		return (1);
	return (0);
}

int	try_grabbing_forks(t_philo *philo_ptr)
{
	if (!philo_ptr->right_fork->fork || !philo_ptr->left_fork->fork
		|| philo_ptr->tabel->now - philo_ptr->last_meal
		< philo_ptr->tabel->longest_wait - 2)
		return (1);
	if (philo_ptr->idx % 2)
	{
		return (grep_left_fork_first(philo_ptr));
	}
	return (grep_right_fork_first(philo_ptr));
}
