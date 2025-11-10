/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabel_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:13:28 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/06 17:52:01 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	perror_wrong_args(void);

int	init_nums(int argc, char **argv, t_tabel *tabelptr)
{
	if (argc != 5 && argc != 6)
	{
		perror_wrong_args();
		return (1);
	}
	tabelptr->num_forks_is_semed = 0;
	tabelptr->fork_mutex_is_semed = 0;
	tabelptr->write_is_semed = 0;
	tabelptr->weltschmerz_is_semed = 0;
	tabelptr->pids_are_malloced = 0;
	tabelptr->number_each_philo_needs_eat = -1;
	tabelptr->num_philos = safe_atoi(argv[1]);
	tabelptr->time_to_die = safe_atoi(argv[2]);
	tabelptr->time_to_eat = safe_atoi(argv[3]);
	tabelptr->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		tabelptr->number_each_philo_needs_eat = safe_atoi(argv[5]);
	if (tabelptr->num_philos == ERROR_NUM || tabelptr->time_to_die == ERROR_NUM 
		|| tabelptr->time_to_eat == ERROR_NUM
		|| tabelptr->time_to_sleep == ERROR_NUM)
	{
		perror_wrong_args();
		return (1);
	}
	return (0);
}

int	init_weltschmerz(t_tabel *tabelptr)
{
	sem_unlink("/weltschmerz");
	tabelptr->weltschmerz = sem_open("/weltschmerz", O_CREAT | O_EXCL, 0644, 0);
	if (tabelptr->weltschmerz == SEM_FAILED)
		return (1);
	tabelptr->weltschmerz_is_semed = 1;
	sem_unlink("/weltschmerz_mutex");
	tabelptr->weltschmerz_mutex = sem_open("/weltschmerz_mutex",
			O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->weltschmerz_mutex == SEM_FAILED)
		return (1);
	tabelptr->weltschmerz_mutex_is_semed = 1;
	return (0);
}

int	init_sems(t_tabel *tabelptr)
{
	sem_unlink("/sem_num_forks");
	tabelptr->sem_num_forks = sem_open
		("/sem_num_forks", O_CREAT | O_EXCL, 0644, tabelptr->num_philos);
	if (tabelptr->sem_num_forks == SEM_FAILED)
		return (1);
	tabelptr->num_forks_is_semed = 1;
	sem_unlink("/fork_mutex");
	tabelptr->fork_mutex = sem_open("/fork_mutex", O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->fork_mutex == SEM_FAILED)
		return (1);
	tabelptr->fork_mutex_is_semed = 1;
	sem_unlink("/write_mutex");
	tabelptr->write_mutex = sem_open("/write_mutex", O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->write_mutex == SEM_FAILED)
		return (1);
	tabelptr->write_is_semed = 1;
	return (init_weltschmerz(tabelptr));
}

int	malloc_ints(t_tabel *tabelptr)
{
	int	idx;

	idx = 0;
	tabelptr->pids = malloc(sizeof(int) * tabelptr->num_philos);
	if (!tabelptr->pids)
		return (1);
	tabelptr->pids_are_malloced = 1;
	while (idx < tabelptr->num_philos)
	{
		tabelptr->pids[idx] = -1;
		idx ++;
	}
	return (0);
}

int	tabel_set_yourself(int argc, char **argv, t_tabel *tabelptr)
{
	if (init_nums(argc, argv, tabelptr) == 1)
		return (1);
	if (init_sems(tabelptr) == 1)
	{
		printf("ERROR failed to sem\n");
		tabel_clear_yourself(tabelptr);
		return (1);
	}
	if (malloc_ints(tabelptr) == 1)
	{
		printf("ERROR failed to malloc\n");
		tabel_clear_yourself(tabelptr);
		return (1);
	}
	return (0);
}
