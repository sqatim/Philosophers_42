/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:21:31 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/22 17:25:48 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void print(t_philosopher philo)
{
    printf("thread ==> %s\n", (char *)philo.philo);
    printf("number_of_philosopher ==> %d\n", philo.number_of_philosopher);
    printf("time_to_die ==> %d\n", philo.time_to_die);
    printf("time_to_eat ==> %d\n", philo.time_to_eat);
    printf("time_to_sleep ==> %d\n", philo.time_to_sleep);
    printf("number_time_must_eat ==> %d\n", philo.number_time_must_eat);
}