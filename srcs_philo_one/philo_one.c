/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/23 17:51:47 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/errno.h>

int k = 0;
void print_error(int error)
{
    char *str;
    if (error == 1)
        str = "Error in : Number of philosopher\n";
    else if (error == 2)
        str = "Error in : Time to die\n";
    else if (error == 3)
        str = "Error in : Time to eat\n";
    else if (error == 4)
        str = "Error in : Time to sleep\n";
    else if (error == 5)
        str = "Error in : Time to sleep\n";
    else if (error == 6)
        str = "Error in : Number of time each philosophers must eat\n";
    printf("%s", str);
    exit(1);
}

int check_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
void check_arguments(int ac, char **av)
{
    int index;

    index = 1;
    if (ac < 5 || ac > 6)
    {
        printf("error\n");
        exit(1);
    }
    else
    {
        while (av[index])
        {
            if (!check_number(av[index]))
                print_error(index);
            index++;
        }
    }
}

t_philosopher get_args(int ac, char **av)
{
    t_philosopher philo;
    int i;

    i = 0;

    philo.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.number_of_philosopher);
    while (i < philo.number_of_philosopher)
        pthread_mutex_init(&philo.forks[i++], NULL);
    philo.number_of_philosopher = ft_atoi(av[1]);
    philo.i = 0;
    philo.thread = (pthread_t *)malloc(sizeof(pthread_t) * philo.number_of_philosopher);
    philo.state = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
    while (i < philo.number_of_philosopher)
        philo.state[i++] = HUNGER;
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        philo.number_time_must_eat = ft_atoi(av[5]);
    return (philo);
}

void take_fork(t_philosopher *philo, int philosopher)
{
    int fork;

    fork = (philosopher + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    // if (philo->forks[fork] == EMPTY)
    // philo->forks[fork] = FULL;
}

void ft_sleep(t_philosopher *philo)
{
}

void *routine(void *philosopher)
{
    t_philosopher *philo;
    int result;
    philo = (t_philosopher *)philosopher;
    while (1)
    {
        // take_fork(philo, philo->i);
        pthread_mutex_lock(&philo->forks[philo->i]);
        printf("mutex 1 ==> %d\n", k);
        k++;
        pthread_mutex_unlock(&philo->forks[philo->i]);
        sleep(3);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_philosopher philo;
    int i;

    i = 0;
    check_arguments(ac, av);
    philo = get_args(ac, av);
    while (philo.i < philo.number_of_philosopher)
    {
        pthread_create(&philo.thread[philo.i], NULL, &routine, (void *)&philo);
        pthread_detach(philo.thread[philo.i]);
        philo.i++;
    }
    // pthread_join(philo.thread[0], NULL);
    // print(philo);
    i = 0;
    while (i < philo.number_of_philosopher)
        pthread_mutex_destroy(&philo.forks[i++]);
    pthread_exit(0);
}