/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:56 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/07 15:23:38 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	tabel_set_yourself(int argc, char **args, t_tabel *tabel_ptr);
void	*rutine(void *args);

void	philos_do_your_thing(t_tabel *tabel_ptr)
{
	int	idx;

	idx = 0;
	tabel_ptr = tabel_ptr->philos[0].tabel;
	while (idx < tabel_ptr->num_philos)
	{
		tabel_ptr->philos[idx].is_threaded = 1;
		if (pthread_create(&tabel_ptr->philos[idx].thread, NULL,
				&rutine, &(tabel_ptr->philos[idx])) == 0)
			idx ++;
		else
		{
			tabel_ptr->philos[idx].is_threaded = 0;
			set_weltschmerz(tabel_ptr);
			return ;
		}
	}
}

int	main(int argc, char **argv)
{
	t_tabel	tabel;

	tabel_set_yourself(argc, argv, &tabel);
	if (!tabel.weltschmerz)
		philos_do_your_thing(&tabel);
	tabel_clear_yourself(&tabel);
	return (0);
}
