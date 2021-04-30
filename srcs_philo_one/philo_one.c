/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/30 02:42:40 by ragegodthor      ###   ########.fr       */
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

t_data get_args(int ac, char **av)
{
	t_data data;
	int i;

	i = 1;
	data.nb_of_philo = ft_atoi(av[1]);
	data.philo = (t_philo *)malloc(sizeof(t_philo) * data.nb_of_philo);
	data.philo[0].fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data.nb_of_philo);
	data.philo[0].mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data.philo[0].die_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&data.philo[0].fork[0], NULL);
	pthread_mutex_init(&data.philo[0].mutex[0], NULL);
	pthread_mutex_init(&data.philo[0].die_m[0], NULL);
	while (i < data.nb_of_philo)
	{
		pthread_mutex_init(&data.philo[0].fork[i], NULL);
		data.philo[i].fork = data.philo[0].fork;
		data.philo[i].mutex = data.philo[0].mutex;
		data.philo[i].die_m = data.philo[0].die_m;
		i++;
	}
	i = 0;
	while (i < data.nb_of_philo)
	{
		data.philo[i].l = i;
		data.philo[i].r = (i + data.nb_of_philo - 1) % data.nb_of_philo;
		// pthread_mutex_init(&data.philo[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < data.nb_of_philo)
	{
		data.philo[i].nb_of_philo = ft_atoi(av[1]);
		data.philo[i].time_to_die = ft_atoi(av[2]);
		data.philo[i].time_to_eat = ft_atoi(av[3]);
		data.philo[i].time_to_sleep = ft_atoi(av[4]);
		i++;
	}
	if (ac == 6)
		data.number_time_must_eat = ft_atoi(av[5]);
	return (data);
}

pthread_mutex_t *create_forks(int number, int *check)
{
	pthread_mutex_t *fork;
	int i;

	i = 0;
	*check = 0;
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	while (i < number)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void print_msg(t_philo *philo, int number, int x, int fork)
{
	struct timeval current_t;

	pthread_mutex_lock(&philo->mutex[0]);
	gettimeofday(&current_t, NULL);
	if (number == 1)
		printf("%ld %d has taken a right fork[%d]\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, x, fork);
	else if (number == 2)
		printf("%ld %d has taken a left fork[%d]\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, x, fork);
	else if (number == 3)
	{
		philo->starting_t = current_t.tv_sec * 1000 + current_t.tv_usec / 1000 + philo->time_to_eat + philo->time_to_sleep;
		printf("%ld %d is eating\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, x);
	}
	else if (number == 4)
		printf("%ld %d is sleeping\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, x);
	else if (number == 5)
		printf("%ld %d is thinking\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, x);
	else if (number == 6)
		printf("philo %d put forks\n", x);
	pthread_mutex_unlock(&philo->mutex[0]);
}

void *ft_die(void *philosopher)
{
	t_philo *philo;
	struct timeval current_t;
	struct timeval starting_t;

	philo = (t_philo *)philosopher;
	gettimeofday(&starting_t, NULL);
	philo->starting_t = starting_t.tv_sec * 1000 + starting_t.tv_usec / 1000;
	while (1)
	{
		pthread_mutex_lock(&philo->die_m[0]);
		gettimeofday(&current_t, NULL);
		if ((current_t.tv_sec * 1000 + current_t.tv_usec / 1000) - philo->starting_t >= philo->time_to_die)
		{
			printf("%ld %d died\n", current_t.tv_sec * 1000 + current_t.tv_usec / 1000, philo->l);
			exit(1);
		}
		pthread_mutex_unlock(&philo->die_m[0]);
	}
}

void *routine(void *philosopher)
{
	t_philo *philo;

	philo = (t_philo *)philosopher;
	// printf("philo %p\n", philo->l);

	pthread_create(&philo->die_p, NULL, &ft_die, (void *)philo);
	pthread_detach(philo->die_p);

	// sleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->r]);
		print_msg(philo, 1, philo->l, philo->r);
		pthread_mutex_lock(&philo->fork[philo->l]);
		print_msg(philo, 2, philo->l, philo->l);
		print_msg(philo, 3, philo->l, 0);
		usleep(philo->time_to_eat * 1000);
		print_msg(philo, 6, philo->l, 0);
		pthread_mutex_unlock(&philo->fork[philo->r]);
		pthread_mutex_unlock(&philo->fork[philo->l]);
		print_msg(philo, 4, philo->l, 0);
		usleep(philo->time_to_sleep * 1000);
		print_msg(philo, 5, philo->l, 0);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_data data;
	int i;
	pthread_t *thread;

	i = 0;
	check_arguments(ac, av);
	data = get_args(ac, av);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * data.nb_of_philo);
	i = 0;
	while (i < data.nb_of_philo)
	{
		// data.philo[i].l = i;
		// data.philo[i].r = (i + data.nb_of_philo - 1) % data.nb_of_philo;
		pthread_create(&thread[i], NULL, &routine, (void *)&data.philo[i]);
		pthread_detach(thread[i]);
		usleep(10);
		i++;
	}
	while (1)
	{
	}
	// i = 0;
	// pthread_join(philo.thread[0], NULL);
	// print(philo);
	i = 0;
	// while (i < data.nb_of_philo)
	// pthread_mutex_destroy(&data.philo[i++].fork);
	// return (0);
}