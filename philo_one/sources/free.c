/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 15:53:03 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	free_philo(t_philo *philo, pthread_t *thread)
{
	free(philo->fork);
	philo->fork = NULL;
	free(philo->each_one);
	philo->each_one = NULL;
	free(philo->die);
	philo->die = NULL;
	free(philo->mutex);
	philo->mutex = NULL;
	free(philo->main);
	philo->main = NULL;
	free(philo);
	philo = NULL;
	free(thread);
	thread = NULL;
}
