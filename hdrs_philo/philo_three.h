/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:41:25 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/05 17:25:53 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

# define FORK_S "/fork"
# define PRINT_S "/print"
# define DIE_S "/die"
# define MAIN_S "/main"
# define EACH_S "/each"


typedef struct s_philosopher
{
    int nbr;
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
    sem_t *main;
    sem_t *die;
    sem_t *each;

    pthread_t die_p;
} t_philo;

typedef struct s_semaphore
{
    sem_t *fork;
    sem_t *print;
    sem_t *main;
    sem_t *die;
    sem_t *each;
} t_sem;

int ft_isdigit(int c);
int ft_atoi(const char *str);
void free_philo(t_philo *philo, pthread_t *thread);

#endif