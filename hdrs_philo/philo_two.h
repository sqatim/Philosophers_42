/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:41:38 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/03 02:37:44 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
#define PHILO_TWO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>

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
    sem_t *fork;
    sem_t *print;

    pthread_t die_p;
} t_philo;

typedef struct s_semaphore
{
    sem_t fork;
    sem_t print;
} t_sem;

int ft_isdigit(int c);
int ft_atoi(const char *str);
void free_philo(t_philo *philo, pthread_t *thread);


#endif