/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/04 14:30:47 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void free_philo(t_philo *philo, pthread_t *thread)
{
    int i;
    int number;

    i = 0;
    sem_close(philo->die);
    sem_close(philo->main);
    sem_close(philo->print);
    sem_close(philo->fork);
    free(philo[0].each_one);
    free(philo);
    free(thread);
}