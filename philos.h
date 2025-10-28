
#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_fork
{
	int				fork; //each fork one int, zero meaning in use and one free
	pthread_mutex_t	mutex;
}	t_fork;

typedef	struct s_tabel
{
	t_fork	*forks;
	int		weltschmerz;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		forks_is_malloced;
	int		pthread_num;
}	t_tabel;

#define THINKING 0
#define SLEEPING 1
#define EATING 2

#define ERROR_NUM -85505

typedef	struct s_philo
{
	int		last_meal;
	t_fork	*left_fork;
	t_fork	*right_fork;
	int		activity;
}	t_philo;

#endif
