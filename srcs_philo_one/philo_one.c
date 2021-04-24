/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/24 15:25:05 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/errno.h>

int k = 0;
pthread_mutex_t mutex;

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
    pthread_mutex_init(&mutex, NULL);
    philo.number_of_philosopher = ft_atoi(av[1]);
    philo.i = 0;
    philo.thread = (pthread_t *)malloc(sizeof(pthread_t) * philo.number_of_philosopher);
    // philo.state_forks = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
    philo.state_philo = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
    while (i < philo.number_of_philosopher)
    {
        philo.state_philo[i++] = HUNGER;
        // philo.state_forks[i++] = EMPTY;
    }
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        philo.number_time_must_eat = ft_atoi(av[5]);
    return (philo);
}

void take_forks(t_philosopher *philo, int philosopher)
{
    int right;
    int left;
    int i;

    i = philosopher;
    right = (i + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    left = (i + 1) / philo->number_of_philosopher;
    pthread_mutex_lock(&mutex);
    philo->state_philo[i] = HUNGER;
    if(philo->state_philo[i] == HUNGER && philo->state_philo[left] != EATING && philo->state_philo[right] != EATING)
    {
        philo->state_philo[i] = EATING;
        pthread_mutex_lock(&philo->forks[i]);
    }
    pthread_mutex_unlock(&mutex);
}

void ft_eating(t_philosopher *philo, int k)
{
    if (philo->state_philo[k] == EATING)
    {
        printf("Philo %d is eating\n", k);
        usleep(philo->time_to_eat * 1000);
        // philo->state_philo[k] = SLEEP;
    }
}

void put_forks(t_philosopher *philo, int philosopher)
{
    int right;
    int left;
    int i;

    // puts("samir");s
    pthread_mutex_lock(&mutex);
    i = philosopher;
    right = (i + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    left = (i + 1) / philo->number_of_philosopher;

    i = right;
    right = (i + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    left = (i + 1) / philo->number_of_philosopher;
    // printf("i/right ==> %d\n", i);
    // printf("right/right ==> %d\n", right);
    // printf("left/right ==> %d\n", left);
    if (philo->state_philo[i] == HUNGER && philo->state_philo[right] != EATING && philo->state_philo[left] != EATING)
    {
        // printf("i ==> %d\n", i);
        philo->state_philo[i] = EATING;
        pthread_mutex_lock(&philo->forks[i]);
        // pthread_mutex_lock(&philo->forks[right]);
    }
    i = philosopher;
    left = (i + 1) / philo->number_of_philosopher;
    i = left;
    right = (i + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    left = (i + 1) / philo->number_of_philosopher;
    if (philo->state_philo[i] == HUNGER && philo->state_philo[right] != EATING && philo->state_philo[left] != EATING)
    {
        // printf("qatim\n");
        pthread_mutex_lock(&philo->forks[i]);
        philo->state_philo[i] = EATING;
        // pthread_mutex_lock(&philo->forks[right]);
    }
    pthread_mutex_unlock(&mutex);
}

void ft_sleep(t_philosopher *philo, int i)
{
    int right;

    right = (i + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    // if (philo->state_philo[i] == SLEEP)
    // {
        pthread_mutex_unlock(&philo->forks[right]);
        printf("Philo %d is sleeping\n", k);
        usleep(philo->time_to_sleep * 1000);
        philo->state_philo[k] = HUNGER;
    // }
}

void *routine(void *philosopher)
{
    t_philosopher *philo;
    int k;
    philo = (t_philosopher *)philosopher;
    k = philo->i;
    int right;
    right = (k + philo->number_of_philosopher - 1) / philo->number_of_philosopher;
    while (1)
    {
        
        take_forks(philo, k);
        // if (philo->state_philo[k] == EATING)
        ft_eating(philo, k);
        put_forks(philo, k);
        // if (philo->state_philo[k] == SLEEP)
        ft_sleep(philo, k);
        // ft_think(philo);
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
    while (i < philo.number_of_philosopher)
    {
        philo.i = i;
        pthread_create(&philo.thread[philo.i], NULL, &routine, (void *)&philo);
        // pthread_detach(philo.thread[philo.i]);
        // sleep(2);
        // sleep(2);
        i++;
    }
    i = 0;
    while(i < philo.number_of_philosopher)
    pthread_join(philo.thread[i++], NULL);
    // pthread_join(philo.thread[0], NULL);
    // print(philo);
    i = 0;
    while (i < philo.number_of_philosopher)
        pthread_mutex_destroy(&philo.forks[i++]);
        return(0);
    // pthread_exit(0);
}