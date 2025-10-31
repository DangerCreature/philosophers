/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:24:17 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/31 18:19:27 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_tabel
{
	sem_t	*sem_num_forks;
	char	num_forks_is_semed;
	sem_t	*sem_fork;
	char	fork_is_semed;
	sem_t	*sem_write;
	char	write_is_semed;
	sem_t	*weltschmerz;
	char	weltschmerz_is_semed;
	int		*pids;
	char	pids_are_malloced;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}	t_tabel;

typedef struct s_philo
{
	int		*pids_of_mom;
	sem_t	*sem_num_forks;
	sem_t	*fork_sem;
	sem_t	*write_sem;
	sem_t	*weltschmerz;
	long	time;
	long	last_meal;
	long	last_sleep;
	int		num_meals;
	int		time_to_die;
	int		ime_to_eat;
	int		time_to_sleep;
	int		times_each_philo_needs_eat;
	int		activity;
}	t_philo;

int	safe_atoi(const char *nptr);

# define THINKING 0
# define SLEEPING 1
# define EATING 2
# define FORK_GRAB 3
# define FORK_RETURN 4
# define DIED 5
# define IT_IS_ENOUGH 6
# define ERROR_NUM -85505
/*
void	tabel_clear_yourself(t_tabel *tabel);
int		status_update(t_philo philo, int status_type);
int		set_now_to_now(t_tabel *tabel_ptr);
int		let_go_of_fork(t_fork *fork_ptr, t_philo philo);
*/
#endif
