/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:40:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/23 23:36:45 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define EMPTY 0
#define FULL 1
#define HUNGER 2
#define EATING 3
#define THOUGHT 4
#define SLEEP 5

typedef struct s_philosopher
{
    pthread_t *thread;
    pthread_mutex_t *forks;
    // int *state_forks;
    int *state_philo;
    int i;
    int number_of_philosopher;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_time_must_eat;
} t_philosopher;

int ft_isdigit(int c);
int ft_atoi(const char *str);
void print(t_philosopher philo);

#endif