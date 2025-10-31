/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:15:05 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/31 18:39:46 by gwolfrum         ###   ########.fr       */
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

int	init_nums(int argc, char **argv, t_tabel *tabelptr)
{
	tabelptr->num_forks_is_semed = 0;
	tabelptr->fork_is_semed = 0;
	tabelptr->write_is_semed = 0;
	tabelptr->weltschmerz_is_semed = 0;
	tabelptr->pids_are_malloced = 0;
	if (argc != 5 && argc != 6)
	{
		perror_wrong_args();
		return (1);
	}
	tabelptr->num_philos = safe_atoi(argv[1]);
	tabelptr->time_to_die = safe_atoi(argv[2]);
	tabelptr->time_to_eat = safe_atoi(argv[3]);
	tabelptr->time_to_sleep = safe_atoi(argv[4]);
	if (tabelptr->num_philos == ERROR_NUM || tabelptr->time_to_die == ERROR_NUM 
		|| tabelptr->time_to_eat == ERROR_NUM || tabelptr->time_to_sleep == ERROR_NUM)
	{
		perror_wrong_args();
		return (1);
	}
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
	sem_unlink("/sem_fork");
	tabelptr->sem_fork = sem_open("/sem_fork", O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->sem_fork == SEM_FAILED)
		return (1);
	tabelptr->fork_is_semed = 1;
	sem_unlink("/sem_write");
	tabelptr->sem_write = sem_open("/sem_write", O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->sem_write == SEM_FAILED)
		return (1);
	tabelptr->write_is_semed = 1;
	sem_unlink("/weltschmerz");
	tabelptr->weltschmerz = sem_open("/weltschmerz", O_CREAT | O_EXCL, 0644, 1);
	if (tabelptr->weltschmerz == SEM_FAILED)
		return (1);
	tabelptr->weltschmerz_is_semed = 1;
	return (0);
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

void	clear_threads(t_tabel *tabelptr)
{
	if (tabelptr->num_forks_is_semed)
	{
		sem_close(tabelptr->sem_num_forks);
		sem_unlink("/sem_num_forks");
		tabelptr->num_forks_is_semed = 0;
	}
	if (tabelptr->fork_is_semed)
	{
		sem_close(tabelptr->sem_fork);
		sem_unlink("/sem_fork");
		tabelptr->fork_is_semed = 0;
	}
	if (tabelptr->write_is_semed)
	{
		sem_close(tabelptr->sem_write);
		sem_unlink("/sem_write");
		tabelptr->write_is_semed = 0;
	}
	if (tabelptr->weltschmerz_is_semed)
	{
		sem_close(tabelptr->weltschmerz);
		sem_unlink("/weltschmerz");
		tabelptr->weltschmerz_is_semed = 0;
	}
}

void	tabel_clear_yourself(t_tabel *tabelptr)
{
	int	idx;

	idx = 0;
	if (tabelptr->pids_are_malloced)
	{
		while (idx < tabelptr->num_philos)
		{
			if (tabelptr->pids[idx] != -1)
				waitpid(tabelptr->pids[idx], NULL, 0);
			idx ++;
		}
		free(tabelptr->pids);
		tabelptr->pids_are_malloced = 0;
	}
	clear_threads(tabelptr);
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

int	main(int argc, char *argv[])
{
	t_tabel	tabel;
	if (tabel_set_yourself(argc, argv, &tabel))
		return (1);
	tabel_clear_yourself(&tabel);
	return (0);
}
