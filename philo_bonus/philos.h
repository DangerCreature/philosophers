/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:24:17 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 10:58:53 by gwolfrum         ###   ########.fr       */
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
	sem_t	*fork_mutex;
	char	fork_mutex_is_semed;
	sem_t	*write_mutex;
	char	write_is_semed;
	sem_t	*weltschmerz;
	char	weltschmerz_is_semed;
	sem_t	*weltschmerz_mutex;
	char	weltschmerz_mutex_is_semed;
	int		*pids;
	char	pids_are_malloced;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_each_philo_needs_eat;
}	t_tabel;

typedef struct s_philo
{
	int		idx;
	long	time;
	long	last_meal;
	long	last_sleep;
	int		num_meals;
	int		activity;
	t_tabel	*tabelptr;
}	t_philo;

typedef struct s_pthread_input
{
	sem_t			*sem;
	int				out;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	internal_mutex;
}	t_pthread_input;

int		safe_atoi(const char *nptr);
int		tabel_set_yourself(int argc, char **argv, t_tabel *tabelptr);
void	tabel_clear_yourself(t_tabel *tabelptr);
long	now(void);
int		ft_sem_trywait(t_pthread_input input);
void	status_update(t_philo philo, int status_type, char *error_msg);
void	chiald_die(t_philo philo);
t_philo	birth(t_tabel *tabelptr);
int		weltschmerz_is(t_philo *philoptr, t_tabel tabel);
int		try_grabbing_forks(t_philo *philoptr, t_tabel tabel);
long	clean_now(t_philo *philoptr, t_tabel tabel);

# define THINKING 0
# define SLEEPING 1
# define EATING 2
# define FORK_GRAB 3
# define FORK_RETURN 4
# define DIED 5
# define IT_IS_ENOUGH 6
# define ERROR_NUM -85505

#endif
