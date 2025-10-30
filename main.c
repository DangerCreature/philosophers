/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:56 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/30 17:04:57 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	tabel_set_yourself(int argc, char **args, t_tabel *tabel_ptr);
void	*rutine(void *args);

int	is_it_enough_eating(t_tabel *tabel_ptr)
{
	int	idx;

	if (tabel_ptr->times_each_philo_needs_eat == -1)
		return (1);
	idx = 0;
	while (idx < tabel_ptr->num_philos)
	{
		if (tabel_ptr->philos[idx].num_meals
			< tabel_ptr->times_each_philo_needs_eat)
			return (1);
		idx ++;
	}
	tabel_ptr->weltschmerz = 1;
	status_update(tabel_ptr->philos[0], IT_IS_ENOUGH);
	return (1);
}

void	find_longest_wait(t_tabel *tabel_ptr)
{
	int		idx;
	long	longest_wait;
	long	this_wait;

	idx = 0;
	longest_wait = 0;
	while (idx < tabel_ptr->num_philos)
	{
		this_wait = tabel_ptr->now - tabel_ptr->philos[idx].last_meal;
		if (this_wait > longest_wait)
			longest_wait = this_wait;
		idx ++;
	}
	tabel_ptr->longest_wait = longest_wait;
}

void	philos_do_your_thing(t_tabel *tabel_ptr)
{
	int	idx;

	idx = 0;
	tabel_ptr = tabel_ptr->philos[0].tabel;
	set_now_to_now(tabel_ptr);
	while (idx < tabel_ptr->num_philos)
	{
		if (pthread_create(&tabel_ptr->philos[idx].thread, NULL,
				&rutine, &(tabel_ptr->philos[idx])) == 0)
			tabel_ptr->philos[idx].is_threaded = 1;
		else
		{
			tabel_ptr->weltschmerz = 1;
			return ;
		}
		idx ++;
	}
	while (tabel_ptr->weltschmerz == 0)
	{
		find_longest_wait(tabel_ptr);
		is_it_enough_eating(tabel_ptr);
		set_now_to_now(tabel_ptr);
		usleep(300);
	}
}

int	main(int argc, char **argv)
{
	t_tabel	tabel;

	tabel_set_yourself(argc, argv, &tabel);
	philos_do_your_thing(&tabel);
	tabel_clear_yourself(&tabel);
	return (0);
}
