/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:40:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/30 01:58:25 by ragegodthor      ###   ########.fr       */
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
#define THINKING 4
#define SLEEPING 5

typedef struct s_philosopher
{
    int r;
    int l;
    int nb_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    long starting_t;
    long current_t;
    pthread_mutex_t *fork;
    pthread_mutex_t *mutex;
    pthread_mutex_t *die_m;
    pthread_t die_p;

    // int s_thinking;
    // int s_eating;
    // int s_sleeping;
} t_philo;

typedef struct s_data
{

    t_philo *philo;
    int nb_of_philo;
    // int time_to_die;
    // int time_to_eat;
    // int time_to_sleep;
    int number_time_must_eat;
} t_data;

int ft_isdigit(int c);
int ft_atoi(const char *str);
void print(t_data data);

#endif