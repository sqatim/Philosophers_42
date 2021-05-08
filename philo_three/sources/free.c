/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 05:26:19 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	free_philo(t_philo *philo)
{
	int i;

	i = 0;
	sem_unlink(FORK_S);
	sem_unlink(PRINT_S);
	sem_unlink(DIE_S);
	sem_unlink(MAIN_S);
	sem_unlink(EAT_S);
	sem_unlink(EACH_S);
	sem_unlink(BLOCK_S);
	sem_unlink(INCREMENT_S);
	while(i < philo->nb_of_philo)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
	free(philo->each_one);
	philo->each_one = NULL;
	free(philo);
	philo = NULL;
}
