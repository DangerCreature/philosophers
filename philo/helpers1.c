/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:05:06 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/10 10:11:25 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

static int	ft_isspace(unsigned char c)
{
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	safe_atoi(const char *nptr)
{
	long	out;
	int		sign;

	out = 0;
	sign = 1;
	if (!nptr)
		return (ERROR_NUM);
	while (ft_isspace((unsigned char)*nptr))
		nptr++;
	while (ft_isdigit(*nptr) == 1)
	{
		out = (10 * out) + *nptr - '0';
		if (out < -2147483648)
			return (ERROR_NUM);
		nptr++;
	}
	if (*nptr || out * sign > 2147483647)
		return (ERROR_NUM);
	return ((int)(sign * out));
}

int	status_update(t_philo philo, int status_type)
{
	long	timestmp;
	int		out;

	out = 0;
	timestmp = now() - philo.tabel->time;
	pthread_mutex_lock(&philo.tabel->write_mutex);
	if (status_type == FORK_GRAB)
		out = printf("%ld	%d has taken a fork\n", timestmp, philo.idx + 1);
	else if (status_type == FORK_RETURN)
		out = 0;
	else if (status_type == EATING)
		out = printf("%ld	%d is eating\n", timestmp, philo.idx + 1);
	else if (status_type == SLEEPING)
		out = printf("%ld	%d is sleeping\n", timestmp, philo.idx + 1);
	else if (status_type == THINKING)
		out = printf("%ld	%d is thinking\n", timestmp, philo.idx + 1);
	else if (status_type == DIED)
		out = printf("%ld	%d died\n", timestmp, philo.idx + 1);
	pthread_mutex_unlock(&philo.tabel->write_mutex);
	return (out < 0);
}

long	now(void)
{
	struct timeval	t_now;
	long			now;

	if (gettimeofday(&t_now, NULL) == -1)
		now = -1;
	else
		now = t_now.tv_sec * 1000 + t_now.tv_usec / 1000;
	return (now);
}
