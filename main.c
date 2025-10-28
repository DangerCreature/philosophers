/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:56 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/28 11:49:50 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	safe_atoi(const char *nptr);

void	perror_wrong_args(void)
{
	printf("wrong input\n");
	printf("expecdet: number_of_philosophers");
	printf("time_to_die time_to_eat time_to_sleep\n");
}

void	check_input(int	argc, char **argv, t_tabel *tabel)
{
	if (argc != 5 && argc != 4)
	{
		tabel->weltschmerz = 1;
		return (perror_wrong_args());
	}
	tabel->num_philos = safe_atoi(argv[1]);
	tabel->time_to_die = safe_atoi(argv[2]);
	tabel->time_to_eat = safe_atoi(argv[3]);
	tabel->time_to_sleep = safe_atoi(argv[4]);
	if (tabel->num_philos == ERROR_NUM || tabel->time_to_die == ERROR_NUM 
		|| tabel->time_to_eat == ERROR_NUM || tabel->time_to_sleep == ERROR_NUM)
		tabel->weltschmerz = 1;
}

t_tabel	tabel_set_yourself(int argc, char **args)
{
	t_tabel	tabel;

	tabel.weltschmerz = 0;
	tabel.forks_is_malloced = 0;
	tabel.pthread_num = 0;
	check_input(argc, args, &tabel);
	if (tabel.weltschmerz)
		return (tabel);
	tabel.forks = (t_fork *)malloc(sizeof(t_fork) * tabel.num_philos);
	if (!tabel.forks)
	{
		tabel.weltschmerz = 1;
		return (tabel);
	}
	tabel.forks_is_malloced = 1;
	while (tabel.pthread_num < tabel.num_philos && !tabel.weltschmerz)
	{
		tabel.forks[tabel.pthread_num].fork = 0;
		if (pthread_mutex_init(
				&(tabel.forks[tabel.pthread_num].mutex), NULL) == -1)
			tabel.weltschmerz = 1;
		tabel.pthread_num++;
	}
	return (tabel);
}

void	tabel_clear_yourself(t_tabel tabel)
{
	int	idx;

	idx = 0;
	if (!tabel.forks_is_malloced)
		return ;
	while (idx < tabel.pthread_num - 1)
	{
		pthread_mutex_destroy(&tabel.forks[idx++].mutex);
	}
	free(tabel.forks);
}

t_philo	birth(t_tabel tabel, int philo_idx)
{
	t_philo	baby;

	baby.last_meal = 0;
	baby.left_fork = &tabel.forks[philo_idx];
	baby.right_fork = &tabel.forks[(philo_idx + 1) % tabel.num_philos];
	baby.activity = -1;
	return (baby);
}

int	main(int argc, char **argv)
{
	t_tabel	tabel;
	t_philo	philo1;

	tabel = tabel_set_yourself(argc, argv);
	if (!tabel.weltschmerz)
		philo1 = birth(tabel, 0);
	tabel_clear_yourself(tabel);
	return (0);
}
