/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:40:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/22 17:22:13 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    pthread_t *philo;
    int number_of_philosopher;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_time_must_eat;
}               t_philosopher;


int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void print(t_philosopher philo);

#endif