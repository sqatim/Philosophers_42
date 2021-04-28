/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:21:31 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/26 22:54:12 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void print(t_data data)
{
    int i = 0;
    // printf("thread ==> %s\n", (char *)philo.thread);
    printf("number_of_philosopher ==> %d\n", data.nb_of_philo);
    // while (i < philo.number_of_philosopher)
    // {
    //     printf("fork[%d] ==> %d\n", i, philo.forks[i]);
    //     i++;
    // }
    printf("time_to_die ==> %d\n", data.time_to_die);
    printf("time_to_eat ==> %d\n", data.time_to_eat);
    printf("time_to_sleep ==> %d\n", data.time_to_sleep);
    printf("number_time_must_eat ==> %d\n", data.number_time_must_eat);
}