/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 18:48:51 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 14:07:00 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	perror_wrong_args(void)
{
	printf("wrong input\n");
	printf("expecdet: number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_each_philo_has_to_eat]\n");
}

int	weltschmerz_is(t_tabel *tabelptr)
{
	int	out;

	pthread_mutex_lock(&tabelptr->weltschmerz_mutex);
	out = tabelptr->weltschmerz;
	pthread_mutex_unlock(&tabelptr->weltschmerz_mutex);
	return (out);
}

void	set_weltschmerz(t_tabel *tabelptr)
{
	pthread_mutex_lock(&tabelptr->weltschmerz_mutex);
	tabelptr->weltschmerz = 1;
	pthread_mutex_unlock(&tabelptr->weltschmerz_mutex);
}

int	fork_is(t_fork *fork)
{
	int	out;

	pthread_mutex_lock(&fork->mutex);
	out = fork->fork;
	pthread_mutex_unlock(&fork->mutex);
	return (out);
}
