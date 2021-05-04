/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:45:55 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/04 17:05:38 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

void affectation(int ac, char **av, t_philo **philo)
{
    int number;
    int i;

    i = 0;
    number = ft_atoi(av[1]);
    while (i < number)
    {
        (*philo)[i].number_of_eating = 0;
        (*philo)[i].if_true = 0;
        (*philo)[i].nb_of_philo = number;
        (*philo)[i].time_to_die = ft_atoi(av[2]);
        (*philo)[i].time_to_eat = ft_atoi(av[3]);
        (*philo)[i].time_to_sleep = ft_atoi(av[4]);
        (*philo)[i].nbr = i;
        if (ac == 6)
        {
            (*philo)[i].if_true = 1;
            (*philo)[i].number_time_must_eat = ft_atoi(av[5]);
        }
        i++;
    }
}

t_philo *get_args(int ac, char **av, pthread_t **thread, t_sem *semaphore)
{
    t_philo *philo;
    int number;
    int i;

    number = ft_atoi(av[1]);
    philo = (t_philo *)malloc(sizeof(t_philo) * number);
    affectation(ac, av, &philo);
    *thread = (pthread_t *)malloc(sizeof(pthread_t) * number);
    philo->each_one = (int *)malloc(sizeof(int));
    philo->each_one[0] = 0;
    int err;
    sem_unlink("print");
    sem_unlink("main");
    sem_unlink("die");
    err = sem_unlink("/fork");
    printf("[%i]",err);
    semaphore->fork = sem_open("/sfork", O_CREAT | O_EXCL, S_IREAD | S_IWRITE, 5);
    semaphore->print = sem_open("sprint",O_CREAT | O_EXCL, S_IREAD | S_IWRITE, 1);
    semaphore->main = sem_open("smain", O_CREAT | O_EXCL, S_IREAD | S_IWRITE, 1);
    semaphore->die = sem_open("die", O_CREAT | O_EXCL, S_IREAD | S_IWRITE, 1);
    // sem_init(&semaphore->print, 0, 1);
    i = 0;
    while (i < number)
    {
        philo[i].fork = semaphore->fork;
        philo[i].print = semaphore->print;
        philo[i].main = semaphore->main;
        philo[i].die = semaphore->die;
        if (i != 0)
            philo[i].each_one = philo->each_one;
        i++;
    }
    return (philo);
}

long get_time(long starting_t)
{
    struct timeval current_t;
    long current;

    gettimeofday(&current_t, NULL);
    current = (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
    return (current - starting_t);
}

void print_msg(t_philo *philo, int number, int nbr)
{
    struct timeval current_t;
    long interval;

    sem_wait(philo->print);
    gettimeofday(&current_t, NULL);
    interval = get_time(philo->starting_t_p);
    if (number == 1)
        printf("%ld %d has taken a fork\n", interval, nbr + 1);
    else if (number == 2)
        printf("%ld %d has taken a fork\n", interval, nbr + 1);
    else if (number == 3)
    {
        philo->starting_t_d = current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
        printf("%ld %d is eating\n", interval, nbr + 1);
    }
    else if (number == 4)
        printf("%ld %d is sleeping\n", interval, nbr + 1);
    else if (number == 5)
        printf("%ld %d is thinking\n", interval, nbr + 1);
    else if (number == 6)
        printf("%ld philo %d put forks\n", interval, nbr + 1);
    sem_post(philo->print);

    // pthread_mutex_unlock(&philo->mutex[0]);
}

void *ft_die(void *philosopher)
{
    t_philo *philo;
    long interval;
    struct timeval starting_t;

    philo = (t_philo *)philosopher;
    gettimeofday(&starting_t, NULL);
    philo->starting_t_d = philo->starting_t_p;
    while (1)
    {
        if (sem_wait(philo->die))
            break;
        interval = get_time(philo->starting_t_d);
        if (interval > philo->time_to_die)
        {
            sem_wait(philo->print);
            interval = get_time(philo->starting_t_p);
            printf("%ld %d died\n", interval, philo->nbr + 1);
            sem_post(philo->main);
            break;
        }
        if (sem_post(philo->die))
            break;
        usleep(3000);
    }
    return (NULL);
}

void *routine(void *philosopher)
{
    t_philo *philo;
    struct timeval starting_t;

    philo = (t_philo *)philosopher;
    pthread_create(&philo->die_p, NULL, &ft_die, (void *)philo);
    pthread_detach(philo->die_p);
    while (1)
    {
        if(sem_wait(philo->fork))
            break;
        print_msg(philo, 1, philo->nbr);
        if(sem_wait(philo->fork))
            break;
        print_msg(philo, 2, philo->nbr);
        print_msg(philo, 3, philo->nbr);
        usleep(philo->time_to_eat * 1000);
        if (philo->if_true == 1 && philo->number_of_eating < philo->number_time_must_eat)
        {
            philo->number_of_eating++;
            philo->each_one[0]++;
            if (philo->each_one[0] == philo->nb_of_philo * philo->number_time_must_eat)
            {
                printf("done\n");
                sem_post(philo->main);
                break;
            }
        }
        sem_post(philo->fork);
        sem_post(philo->fork);
        if (philo->if_true == 1 && philo->number_of_eating == philo->number_time_must_eat)
            break;
        print_msg(philo, 6, philo->nbr);
        print_msg(philo, 4, philo->nbr);
        usleep(philo->time_to_sleep * 1000);
        print_msg(philo, 5, philo->nbr);
        usleep(40);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    t_philo *philo;
    pthread_t *thread;
    t_sem semaphore;
    struct timeval starting_t;
    int i;

    check_arguments(ac, av);
    philo = get_args(ac, av, &thread, &semaphore);
    i = 0;
    sem_wait(semaphore.main);
    gettimeofday(&starting_t, NULL);
    while (i < philo[0].nb_of_philo)
    {
        philo[i].starting_t_p = starting_t.tv_sec * 1000 + starting_t.tv_usec / 1000;
        i++;
    }
    i = 0;
    while (i < philo->nb_of_philo)
    {
        pthread_create(&thread[i], NULL, &routine, (void *)&philo[i]);
        pthread_detach(thread[i]);
        usleep(20);
        i++;
    }
    sem_wait(semaphore.main);
    free_philo(philo, thread);
    return (0);
}