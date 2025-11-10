/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:15:05 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/11/06 17:42:18 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	rutine(t_philo *philoptr);

int	philos_do_my_bidding(t_tabel *tabelptr)
{
	int		idx;
	t_philo	philo;

	idx = 0;
	philo = birth(tabelptr);
	while (idx < tabelptr->num_philos)
	{
		philo.idx = idx;
		tabelptr->pids[idx] = fork();
		if (tabelptr->pids[idx] == 0)
			rutine(&philo);
		if (tabelptr->pids[idx] == -1)
		{
			status_update(philo, ERROR_NUM, "fork_failed");
			return (1);
		}
		idx ++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_tabel	tabel;

	if (tabel_set_yourself(argc, argv, &tabel))
		return (1);
	philos_do_my_bidding(&tabel);
	tabel_clear_yourself(&tabel);
	return (0);
}
