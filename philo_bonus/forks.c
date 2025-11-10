/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:22:04 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/06 17:52:24 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	trywait_init(t_pthread_input *input, sem_t *sem, t_philo *philoptr);

int	duble_sem_trywait(t_pthread_input input, t_philo *philoptr)
{
	int	out;

	out = ft_sem_trywait(input);
	if (out == 0)
	{
		out = ft_sem_trywait(input);
		if (out == 0)
		{
			philoptr->activity = EATING;
		}
		else
			sem_post(input.sem);
	}
	return (out);
}

int	try_grabbing_forks(t_philo *philoptr, t_tabel tabel)
{
	t_pthread_input	input;
	int				out;

	out = -1;
	input.mutex = &input.internal_mutex;
	trywait_init(&input, tabel.sem_num_forks, philoptr);
	sem_wait(tabel.fork_mutex);
	out = duble_sem_trywait(input, philoptr);
	sem_post(tabel.fork_mutex);
	pthread_mutex_destroy(input.mutex);
	usleep(150);
	if (philoptr->activity == EATING)
	{
		status_update(*philoptr, FORK_GRAB, NULL);
		status_update(*philoptr, FORK_GRAB, NULL);
	}
	if (out == -1)
	{
		status_update(*philoptr, ERROR_NUM, "threading_failed");
		sem_post(tabel.weltschmerz);
		chiald_die(*philoptr);
	}
	return (out);
}

int	let_go_of_fork(t_philo philo, t_tabel tabel)
{
	sem_post(tabel.sem_num_forks);
	status_update(philo, FORK_RETURN, NULL);
	return (0);
}
