/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:21:31 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/23 00:25:49 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void print(t_philosopher philo)
{
    int i = 0;
    // printf("thread ==> %s\n", (char *)philo.thread);
    printf("number_of_philosopher ==> %d\n", philo.number_of_philosopher);
    while (i < philo.number_of_philosopher)
        printf("fork[%d] ==> %d\n", i, philo.forks[i++]);
    printf("time_to_die ==> %d\n", philo.time_to_die);
    printf("time_to_eat ==> %d\n", philo.time_to_eat);
    printf("time_to_sleep ==> %d\n", philo.time_to_sleep);
    printf("number_time_must_eat ==> %d\n", philo.number_time_must_eat);
}