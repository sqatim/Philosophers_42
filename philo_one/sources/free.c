/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 02:42:42 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	destroy_mutex(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->nb_of_philo)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		pthread_mutex_destroy(&philo->die[i]);
		i++;
	}
	pthread_mutex_destroy(philo->main);
	pthread_mutex_destroy(philo->block);
	pthread_mutex_destroy(philo->increment);
	pthread_mutex_destroy(philo->print);
}

void	free_philo(t_philo **philo, pthread_t *thread)
{
	destroy_mutex(*philo);
	free(thread);
	thread = NULL;
	free((*philo)->print);
	(*philo)->print = NULL;
	free((*philo)->block);
	(*philo)->block = NULL;
	free((*philo)->increment);
	(*philo)->increment = NULL;
	free((*philo)->each_one);
	(*philo)->each_one = NULL;
	free((*philo)->fork);
	(*philo)->fork = NULL;
	free((*philo)->die);
	(*philo)->die = NULL;
	free((*philo)->main);
	(*philo)->main = NULL;
	free((*philo));
	(*philo) = NULL;
}
