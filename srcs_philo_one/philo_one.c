/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/29 16:37:48 by sqatim           ###   ########.fr       */
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
	pthread_mutex_init(&data.philo[0].fork[0], NULL);
	while (i < data.nb_of_philo)
	{
		pthread_mutex_init(&data.philo[0].fork[i], NULL);
		data.philo[i].fork = data.philo[0].fork;
		// printf("adress fork[%d] ==> %p|\t|adress fork[0] ==> %p\n", i,data.philo[i].fork, data.philo[0].fork);
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

// int test(int k, t_data *data)
// {
// 	int right;
// 	int left;

// 	pthread_mutex_lock(&mutex1);
// 	right = (k + data->nb_of_philo - 1) % data->nb_of_philo;
// 	left = (k + 1) % data->nb_of_philo;
// 	if (data->philo[k].state == HUNGER && data->philo[right].state != EATING && data->philo[left].state != EATING)
// 	{
// 		data->philo[k].s_fork = FULL;
// 		data->philo[k].state = EATING;
// 		pthread_mutex_unlock(&mutex1);
// 		return (1);
// 	}
// 	// else
// 	// 	data->philo[k].state = THINKING;
// 	pthread_mutex_unlock(&mutex1);
// 	return (0);
// }
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
void *routine(void *philosopher)
{
	t_philo *philo;
	// static int check;
	int i;
	// static pthread_mutex_t *fork;

	philo = (t_philo *)philosopher;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->fork[philo->r]);
		printf("philo %d take the right fork[%d]\n", philo->l, philo->r);
		pthread_mutex_lock(&philo->fork[philo->l]);
		printf("philo %d take the left fork[%d]\n", philo->l, philo->l);
		printf("philo %d start eating\n", philo->l);
		usleep(philo->time_to_eat * 1000);
		printf("philo %d put forks\n", philo->l);
		pthread_mutex_unlock(&philo->fork[philo->r]);
		pthread_mutex_unlock(&philo->fork[philo->l]);
		printf("philo %d start sleeping\n", philo->l);
		usleep(philo->time_to_sleep * 1000);
		printf("philo %d start thinking\n", philo->l);
	}
	i = 0;
	// while (i < philo->nb_of_philo)
	// pthread_mutex_destroy(&fork[i++]);
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
		data.philo[i].l = i;
		data.philo[i].r = (i + data.nb_of_philo - 1) % data.nb_of_philo;
		pthread_create(&thread[i], NULL, &routine, (void *)&data.philo[i]);
		pthread_detach(thread[i]);
		usleep(20);
		i++;
	}
	while (1)
		;
	printf("salammmmmmm");
	// i = 0;
	// pthread_join(philo.thread[0], NULL);
	// print(philo);
	i = 0;
	// while (i < data.nb_of_philo)
	// pthread_mutex_destroy(&data.philo[i++].fork);
	// return (0);
	// pthread_exit(0);
}