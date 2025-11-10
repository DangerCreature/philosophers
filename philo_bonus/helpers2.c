/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 17:45:29 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/06 17:50:31 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long	find_gcd(long a, long b)
{
	long	r;

	if (a < b)
	{
		r = a;
		a = b;
		b = r;
	}
	while (a % b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return (b);
}

long	clean_now(t_philo *philoptr, t_tabel tabel)
{
	long	gcd;
	long	clean_now;

	clean_now = now();
	gcd = find_gcd(tabel.time_to_sleep, tabel.time_to_eat);
	clean_now -= (clean_now - philoptr->time) % gcd;
	return (clean_now);
}

void	perror_wrong_args(void)
{
	printf("wrong input\n");
	printf("expecdet: number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_each_philo_needs_eat]\n");
}
