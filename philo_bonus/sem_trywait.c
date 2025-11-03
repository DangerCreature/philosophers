/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_trywait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:34:32 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/03 17:57:30 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*ft_sem_wait(void *args)
{
	t_pthread_input	*inputptr;

	inputptr = (t_pthread_input *) args;
	sem_wait(inputptr->sem);
	pthread_mutex_lock(&inputptr->mutex);
	inputptr->out = 0;
	pthread_mutex_unlock(&inputptr->mutex);
	return (args);
}

int	weltschmerz_is(t_philo *philoptr, t_tabel tabel)
{
	int	out;

	out = ft_sem_trywait(tabel.weltschmerz, tabel.weltschmerz_mutex);
	if (out == -1)
	{
		status_update(*philoptr, ERROR_NUM, "ERROR: thread_create failed");
		sem_post(tabel.weltschmerz);
		chiald_die(*philoptr);
	}
	return (out);
}

int	ft_sem_trywait(sem_t *sem, sem_t *sem_mutex)
{
	t_pthread_input	input;
	pthread_t		pthread;
	int				out;

	out = 0;
	input.sem = sem;
	input.out = 1;
	pthread_mutex_init(&input.mutex, NULL);
	sem_wait(sem_mutex);
	if (pthread_create(&pthread, NULL, &ft_sem_wait, &input) != 0)
		return (-1);
	usleep(200);
	pthread_mutex_lock(&input.mutex);
	if (input.out == 1)
	{
		out = 1;
		sem_post(sem);
	}
	pthread_mutex_unlock(&input.mutex);
	sem_post(sem_mutex);
	pthread_join(pthread, NULL);
	pthread_mutex_destroy(&input.mutex);
	return (out);
}
