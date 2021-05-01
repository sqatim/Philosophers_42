/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/01 21:44:29 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/errno.h>

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
		(*philo)[i].l = i;
		(*philo)[i].r = (i + number - 1) % number;
		if (ac == 6)
		{
			(*philo)[i].if_true = 1;
			(*philo)[i].number_time_must_eat = ft_atoi(av[5]);
		}
		i++;
	}
}

t_philo *get_args(int ac, char **av, pthread_t **thread)
{
	t_philo *philo;
	int number;
	int i;

	number = ft_atoi(av[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * number);
	affectation(ac, av, &philo);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * number);
	philo[0].each_one = (int *)malloc(sizeof(int));
	philo[0].each_one[0] = 0;
	philo[0].fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	philo[0].test_die_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	philo[0].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo[0].main = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(&philo[0].mutex[0], NULL);
	i = 1;
	pthread_mutex_init(&philo[0].fork[0], NULL);
	pthread_mutex_init(&philo[0].test_die_m[0], NULL);
	pthread_mutex_init(&philo[0].mutex[0], NULL);
	pthread_mutex_init(&philo[0].main[0], NULL);
	pthread_mutex_init(&philo[0].die_m, NULL);
	while (i < number)
	{
		pthread_mutex_init(&philo[0].fork[i], NULL);
		pthread_mutex_init(&philo[0].test_die_m[i], NULL);
		philo[i].fork = philo[0].fork;
		philo[i].test_die_m = philo[0].test_die_m;
		philo[i].mutex = philo[0].mutex;
		philo[i].main = philo[0].main;
		philo[i].each_one = philo[0].each_one;
		pthread_mutex_init(&philo[i].die_m, NULL);
		i++;
	}
	// while (i < number)
	// {
	// 	pthread_mutex_init(&philo[0].fork[i], NULL);
	// 	pthread_mutex_init(&philo[i].die_m, NULL);
	// 	philo[i + 1].fork = philo[0].fork;
	// 	philo[i + 1].mutex = philo[0].mutex;
	// 	philo[i + 1].each_one = philo[0].each_one;
	// 	i++;
	// }
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

void print_msg(t_philo *philo, int number, int x, int fork)
{
	struct timeval current_t;
	long interval;

	pthread_mutex_lock(&philo->mutex[0]);
	gettimeofday(&current_t, NULL);
	interval = get_time(philo->starting_t_p);
	if (number == 1)
		printf("%ld %d has taken a right fork[%d]\n", interval, x, fork);
	else if (number == 2)
		printf("%ld %d has taken a left fork[%d]\n", interval, x, fork);
	else if (number == 3)
	{
		philo->starting_t_d = current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
		printf("%ld %d is eating\n", interval, x);
	}
	else if (number == 4)
		printf("%ld %d is sleeping\n", interval, x);
	else if (number == 5)
		printf("%ld %d is thinking\n", interval, x);
	else if (number == 6)
		printf("%ld philo %d put forks\n", interval, x);
	pthread_mutex_unlock(&philo->mutex[0]);
}

void *ft_die(void *philosopher)
{
	t_philo *philo;
	long interval;
	struct timeval starting_t;

	philo = (t_philo *)philosopher;
	gettimeofday(&starting_t, NULL);
	philo->starting_t_d = starting_t.tv_sec * 1000 + starting_t.tv_usec / 1000;
	while (1)
	{
		pthread_mutex_lock(&philo->test_die_m[philo->l]);
		interval = get_time(philo->starting_t_d);
		if (interval >= philo->time_to_die)
		{
			pthread_mutex_lock(&philo->mutex[0]);
			printf("%ld %d died\n", interval, philo->l);
			pthread_mutex_unlock(&philo->main[0]);
			// exit(1);
			break;
		}
		pthread_mutex_unlock(&philo->test_die_m[philo->l]);
	}
	return (NULL);
}

void *routine(void *philosopher)
{
	t_philo *philo;
	struct timeval starting_t;

	philo = (t_philo *)philosopher;
	gettimeofday(&starting_t, NULL);
	philo->starting_t_p = starting_t.tv_sec * 1000 + starting_t.tv_usec / 1000;
	pthread_create(&philo->die_p, NULL, &ft_die, (void *)philo);
	pthread_detach(philo->die_p);
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->r]);
		print_msg(philo, 1, philo->l, philo->r);
		pthread_mutex_lock(&philo->fork[philo->l]);
		print_msg(philo, 2, philo->l, philo->l);
		pthread_mutex_lock(&philo->test_die_m[philo->l]);
		print_msg(philo, 3, philo->l, 0);
		usleep(philo->time_to_eat * 1000);
		if (philo->if_true == 1 && philo->number_of_eating < philo->number_time_must_eat)
		{
			philo->number_of_eating++;
			philo->each_one[0]++;
			if (philo->each_one[0] == philo->nb_of_philo * philo->number_time_must_eat)
			{
				pthread_mutex_unlock(&philo->main[0]);
				printf("done\n");
				break;
			}
		}
		pthread_mutex_unlock(&philo->test_die_m[philo->l]);
		// print_msg(philo, 6, philo->l, 0);
		pthread_mutex_unlock(&philo->fork[philo->r]);
		pthread_mutex_unlock(&philo->fork[philo->l]);
		if (philo->if_true == 1 && philo->number_of_eating == philo->number_time_must_eat)
			break;
		print_msg(philo, 4, philo->l, 0);
		usleep(philo->time_to_sleep * 1000);
		print_msg(philo, 5, philo->l, 0);
	}
	// printf("dsakljdklsajdklasjkldjsakldkljsdja\n");
	return (NULL);
}

int main(int ac, char **av)
{
	t_philo *philo;
	pthread_t *thread;
	int i;

	check_arguments(ac, av);
	philo = get_args(ac, av, &thread);
	i = 0;
	// lock
	pthread_mutex_lock(&philo[0].main[0]);
	while (i < philo[0].nb_of_philo)
	{
		pthread_create(&thread[i], NULL, &routine, (void *)&philo[i]);
		pthread_detach(thread[i]);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&philo[0].main[0]);
	return (0);
}