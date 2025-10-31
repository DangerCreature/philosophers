/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolfrum <gwolfrum@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:25:44 by gwolfrum          #+#    #+#             */
/*   Updated: 2025/10/31 16:26:19 by gwolfrum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philos.h"


int	main(void)
{
	int	id;
	sem_t	*semptr;

	semptr = sem_open("/sem_forks", O_CREAT | O_EXCL, 0644, 3);
	if (semptr == SEM_FAILED)
		return (perror("sem"), 1);
	id = fork();
	if (id == 0)
	{
		sem_wait(semptr);
		sem_wait(semptr);
		printf("chiald is eating\n");
		usleep(3000000);
		sem_post(semptr);
		sem_post(semptr);
		return (0);
	}
	sem_wait(semptr);
	sem_wait(semptr);
	printf("mother is eating\n");
	usleep(3000000);
	sem_post(semptr);
	sem_post(semptr);
	waitpid(id, NULL, 0);
	sem_close(semptr);
	sem_unlink("/forks");
}
