/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:24:17 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 14:06:47 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_tabel	t_tabel;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	mutex;
}	t_fork;

struct s_tabel
{
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	write_mutex;
	int				write_is_mutexed;
	long			time;
	int				weltschmerz;
	pthread_mutex_t	weltschmerz_mutex;
	int				weltschmerz_is_mutexed;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philo_needs_eat;
	int				philos_are_malleoced;
	int				forks_is_malloced;
	int				pt_m_num;
};

struct s_philo
{
	long		last_meal;
	long		last_sleep;
	int			num_meals;
	t_fork		*left_fork;
	t_fork		*right_fork;
	int			activity;
	pthread_t	thread;
	int			is_threaded;
	t_tabel		*tabel;
	int			idx;
};

# define THINKING 0
# define SLEEPING 1
# define EATING 2
# define FORK_GRAB 3
# define FORK_RETURN 4
# define DIED 5
# define IT_IS_ENOUGH 6
# define ERROR_NUM -85505

void	tabel_clear_yourself(t_tabel *tabel);
int		status_update(t_philo philo, int status_type);
long	now(void);
int		let_go_of_fork(t_fork *fork_ptr, t_philo philo);
int		weltschmerz_is(t_tabel *tabelptr);
void	set_weltschmerz(t_tabel *tabelptr);
int		fork_is(t_fork *fork);

#endif
