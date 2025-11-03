/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 15:22:04 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/03 17:44:49 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	try_grabbing_forks(t_philo *philo_ptr, t_tabel tabel)
{
	int	out;

	out = ft_sem_trywait(tabel.sem_num_forks, tabel.fork_mutex);
	if (out == 0)
	{
		out = ft_sem_trywait(tabel.sem_num_forks, tabel.fork_mutex);
		if (out == 0)
		{
			status_update(*philo_ptr, FORK_GRAB, NULL);
			status_update(*philo_ptr, FORK_GRAB, NULL);
			philo_ptr->activity = EATING;
			return (out);
		}
		sem_post(tabel.sem_num_forks);
	}
	if (out == -1)
	{
		status_update(*philo_ptr, ERROR_NUM, "ERROR: threading_failed\n");
		sem_post(tabel.weltschmerz);
		chiald_die(*philo_ptr);
	}
	return (out);
}

int	let_go_of_fork(t_philo philo, t_tabel tabel)
{
	sem_post(tabel.sem_num_forks);
	status_update(philo, FORK_RETURN, NULL);
	return (0);
}
