/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/01 15:36:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void free_philo(t_philo *philo, pthread_t *thread)
{
    int i;
    int number;

    i = 0;
    number = philo[0].nb_of_philo;
    free(philo[0].fork);
    free(philo[0].each_one);
    free(philo[0].test_die_m);
    free(philo[0].mutex);
    free(philo[0].main);
    free(philo);
    free(thread);
}