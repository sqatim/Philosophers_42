/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:40:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/03 16:13:36 by sqatim           ###   ########.fr       */
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
    int if_true;
    int number_time_must_eat;
    long starting_t_d;
    long starting_t_p;
    long current_t;
    int number_of_eating;
    int *each_one;
    pthread_mutex_t *fork;
    pthread_mutex_t *mutex;
    pthread_mutex_t *main;
    pthread_mutex_t *die;
    pthread_mutex_t *test_die_m;

    pthread_t die_p;
} t_philo;

int ft_isdigit(int c);
int ft_atoi(const char *str);
void    free_philo(t_philo *philo, pthread_t *thread);

#endif