/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:45:44 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/30 17:33:19 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	safe_atoi(const char *nptr);

void	perror_wrong_args(void)
{
	printf("wrong input\n");
	printf("expecdet: number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_each_philo_has_to_eat]\n");
}

void	check_input(int argc, char **argv, t_tabel *tabel)
{
	if (argc != 5 && argc != 6)
	{
		tabel->weltschmerz = 1;
		return (perror_wrong_args());
	}
	tabel->num_philos = safe_atoi(argv[1]);
	tabel->time_to_die = safe_atoi(argv[2]);
	tabel->time_to_eat = safe_atoi(argv[3]);
	tabel->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		tabel->times_each_philo_needs_eat = safe_atoi(argv[5]);
	else 
		tabel->times_each_philo_needs_eat = -1;
	if (tabel->num_philos == ERROR_NUM || tabel->time_to_die == ERROR_NUM 
		|| tabel->time_to_eat == ERROR_NUM || tabel->time_to_sleep == ERROR_NUM)
	{
		tabel->weltschmerz = 1;
		return (perror_wrong_args());
	}
}

void	births(t_tabel *tabel)
{
	int	idx;
	int	next_idx;

	idx = 0;
	while (idx < tabel->num_philos)
	{
		next_idx = ((idx + 1) % (tabel->num_philos));
		tabel->philos[idx].last_meal = tabel->now;
		tabel->philos[idx].last_sleep = tabel->now;
		tabel->philos[idx].left_fork = &tabel->forks[idx];
		tabel->philos[idx].right_fork = &tabel->forks[next_idx];
		tabel->philos[idx].tabel = tabel;
		tabel->philos[idx].activity = -1;
		tabel->philos[idx].idx = idx;
		tabel->philos[idx].is_threaded = 0;
		tabel->philos[idx].num_meals = 0;
		idx ++;
	}
}

void	make_philos_and_forks(t_tabel *tabel)
{
	tabel->forks = (t_fork *)malloc(sizeof(t_fork) * tabel->num_philos);
	if (!tabel->forks)
	{
		tabel->weltschmerz = 1;
		return ;
	}
	tabel->forks_is_malloced = 1;
	tabel->philos = (t_philo *)malloc(sizeof(t_philo) * tabel->num_philos);
	if (!tabel->philos)
	{
		tabel->weltschmerz = 1;
		return ;
	}
	births(tabel);
	tabel->philos_are_malleoced = 1;
	if (pthread_mutex_init(&(tabel->write_mutex), NULL) == -1)
	{
		tabel->weltschmerz = 1;
		return ;
	}
	tabel->write_is_mutexed = 1;
}

void	tabel_set_yourself(int argc, char **args, t_tabel *tabel_ptr)
{
	tabel_ptr->weltschmerz = 0;
	tabel_ptr->forks_is_malloced = 0;
	tabel_ptr->philos_are_malleoced = 0;
	tabel_ptr->write_is_mutexed = 0;
	tabel_ptr->pt_m_num = 0;
	tabel_ptr->longest_wait = 0;
	check_input(argc, args, tabel_ptr);
	if (tabel_ptr->weltschmerz)
		return ;
	set_now_to_now(tabel_ptr);
	make_philos_and_forks(tabel_ptr);
	while (tabel_ptr->pt_m_num < tabel_ptr->num_philos
		&& !tabel_ptr->weltschmerz)
	{
		tabel_ptr->forks[tabel_ptr->pt_m_num].fork = 1;
		if (pthread_mutex_init(
				&(tabel_ptr->forks[tabel_ptr->pt_m_num].mutex), NULL) == -1)
			tabel_ptr->weltschmerz = 1;
		tabel_ptr->pt_m_num++;
	}
	if (tabel_ptr->weltschmerz)
		tabel_clear_yourself(tabel_ptr);
	tabel_ptr->time = tabel_ptr->now;
}
