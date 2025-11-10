/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_trywait.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 15:34:32 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/06 17:48:09 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	*ft_sem_wait(void *args)
{
	t_pthread_input	*inputptr;

	inputptr = (t_pthread_input *) args;
	sem_wait(inputptr->sem);
	pthread_mutex_lock(inputptr->mutex);
	inputptr->out = 0;
	pthread_mutex_unlock(inputptr->mutex);
	return (args);
}

void	trywait_init(t_pthread_input *input, sem_t *sem, t_philo *philoptr)
{
	input->sem = sem;
	input->out = 1;
	if (pthread_mutex_init(input->mutex, NULL) != 0)
	{
		status_update(*philoptr, ERROR_NUM, "pthread_mutex_init failed");
		sem_post(philoptr->tabelptr->weltschmerz);
		chiald_die(*philoptr);
	}
}

int	weltschmerz_is(t_philo *philoptr, t_tabel tabel)
{
	t_pthread_input	input;
	int				out;

	out = -1;
	input.mutex = &input.internal_mutex;
	trywait_init(&input, tabel.weltschmerz, philoptr);
	sem_wait(tabel.weltschmerz_mutex);
	out = ft_sem_trywait(input);
	sem_post(tabel.weltschmerz_mutex);
	usleep(150);
	pthread_mutex_destroy(input.mutex);
	if (out == 0)
		sem_post(tabel.weltschmerz);
	if (out == -1)
	{
		status_update(*philoptr, ERROR_NUM, "pthread_create failed");
		sem_post(tabel.weltschmerz);
		chiald_die(*philoptr);
	}
	return (!out);
}

int	ft_sem_trywait(t_pthread_input input)
{
	pthread_t		pthread;
	int				out;

	out = 0;
	if (pthread_create(&pthread, NULL, &ft_sem_wait, &input) != 0)
		return (-1);
	usleep(150);
	pthread_mutex_lock(input.mutex);
	if (input.out == 1)
	{
		out = 1;
		sem_post(input.sem);
	}
	pthread_mutex_unlock(input.mutex);
	pthread_join(pthread, NULL);
	return (out);
}
