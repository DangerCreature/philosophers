/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:32:22 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/27 15:29:58 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	count;
pthread_mutex_t mutex;

void	*rutine(void *nothing)
{
	int	i;

	i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(&mutex);
		count ++;
		// reed count
		// add count
		// write count
		pthread_mutex_unlock(&mutex);
	}
	return (nothing);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &rutine, NULL) != 0)
		return (1);
	pthread_create(&t2, NULL, &rutine, NULL);
	// the address of pathread var, some exec default (aoto set if NULL) and the funcion address
	// and the final arg is the input parameters.
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// the pathread var and where its rerutnval should be stored
	pthread_mutex_destroy(&mutex);
	printf("counted: %d\n", count);
	return (0);
}
