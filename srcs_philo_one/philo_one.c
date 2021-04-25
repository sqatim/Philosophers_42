/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/25 00:18:28 by ragegodthor      ###   ########.fr       */
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

void *routine(void *philosopher)
{
    t_philosopher *philo;
    int k;
    philo = (t_philosopher *)philosopher;
    pthread_mutex_lock(&mutex);
    k = philo->i;
    printf("%d\n", philo->i);
    pthread_mutex_unlock(&mutex);

    k = 0;
    int right;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (k == philo->number_of_philosopher)
            k = 0;
        // pthread_mutex_lock(&philo->forks[right]);
        // printf("philo %d take the right fork\n", k);
        // k = philo->i;
        // right = (k + philo->number_of_philosopher - 1) / philo->number_of_philosopher;

        right = (k + philo->number_of_philosopher - 1) % philo->number_of_philosopher;
        printf("k ==> %d {==} right ==> %d\n", k, right);
        // printf("%d == %d\n", philo->state_philo[k], philo->state_philo[right]);
        // if (philo->state_philo[k] == HUNGER && philo->state_philo[right] != EATING)
        // {
        //     pthread_mutex_lock(&philo->forks[k]);
        //     printf("philo %d take the left fork\n", k);
        //     printf("philo %d start eating\n", k);
        //     usleep(philo->time_to_eat * 1000);
        // }
        // printf("philo %d put the right fork\n", k);
        // pthread_mutex_unlock(&philo->forks[right]);
        k++;
        sleep(2);
        pthread_mutex_unlock(&mutex);
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
        pthread_create(&philo.thread[i], NULL, &routine, (void *)&philo);
        i++;
    }
    i = 0;
    while (i < philo.number_of_philosopher)
        pthread_join(philo.thread[i++], NULL);
    // pthread_join(philo.thread[0], NULL);
    // print(philo);
    i = 0;
    while (i < philo.number_of_philosopher)
        pthread_mutex_destroy(&philo.forks[i++]);
    return (0);
    // pthread_exit(0);
}