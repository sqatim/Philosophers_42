/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 00:07:59 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	free_philo(t_philo *philo, pthread_t *thread, t_sem *semaphore)
{
	sem_close(semaphore->main);
	sem_close(semaphore->fork);
	sem_close(semaphore->print);
	free(philo[0].each_one);
	free(philo);
	free(thread);
	sem_close(semaphore->die);
}
