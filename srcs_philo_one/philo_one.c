/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/28 02:28:58 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/errno.h>

int k = 0;
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

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

	i = 0;
	data.nb_of_philo = ft_atoi(av[1]);
	// philo.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.number_of_philosopher);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	pthread_mutex_init(&mutex3, NULL);

	// philo.i = 0;
	data.philo = (t_philo *)malloc(sizeof(t_philo) * data.nb_of_philo);
	while (i < data.nb_of_philo)
	{
		pthread_mutex_init(&data.philo[i].fork, NULL);
		i++;
	}
	// philo.state_forks = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
	// philo.state_philo = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
	i = 0;
	while (i < data.nb_of_philo)
	{
		data.philo[i].j = 0;
		data.philo[i].state = HUNGER;
		data.philo[i].s_fork = EMPTY;
		i++;
		// philo.state_forks[i++] = EMPTY;
	}
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.number_time_must_eat = ft_atoi(av[5]);
	return (data);
}

int test(int k, t_data *data)
{
	int right;
	int left;

	pthread_mutex_lock(&mutex1);
	right = (k + data->nb_of_philo - 1) % data->nb_of_philo;
	left = (k + 1) % data->nb_of_philo;
	if (data->philo[k].state == HUNGER && data->philo[right].state != EATING && data->philo[left].state != EATING)
	{
		data->philo[k].s_fork = FULL;
		data->philo[k].state = EATING;
		pthread_mutex_unlock(&mutex1);
		return (1);
	}
	// else
	// 	data->philo[k].state = THINKING;
	pthread_mutex_unlock(&mutex1);
	return (0);
}
void *routine(void *data_philosophers)
{
	t_data *data;
	int right;
	int k;
	int save;
	int savr;

	data = (t_data *)data_philosophers;
	k = data->i;
	right = (k + data->nb_of_philo - 1) % data->nb_of_philo;
	while (1)
	{
		// sleep(1);
		if (data->philo[k].s_fork == EMPTY)
		{
			usleep(40);
			pthread_mutex_lock(&data->philo[k].fork);
			printf("%d take left\n", k);
			data->philo[k].s_fork = FULL;
		}
		if (data->philo[right].s_fork == EMPTY)
		{
			pthread_mutex_lock(&data->philo[right].fork);
			printf("%d take right\n", right);
			data->philo[right].s_fork = FULL;
		}
		
		k++;
		if(k >= data->nb_of_philo)
		right = (k + data->nb_of_philo - 1) % data->nb_of_philo;
	}
	return (NULL);
}

int main(int ac, char **av)
{
	t_data data;
	int i;

	i = 0;
	check_arguments(ac, av);
	data = get_args(ac, av);
	while (i < data.nb_of_philo)
	{
		data.i = i;
		// sleep(1);
		pthread_create(&data.philo[i].thread, NULL, &routine, (void *)&data);
		pthread_detach(data.philo[i].thread);
		i++;
	}
	// i = 0;
	// pthread_join(philo.thread[0], NULL);
	// print(philo);
	i = 0;
	while (i < data.nb_of_philo)
		pthread_mutex_destroy(&data.philo[i++].fork);
	// return (0);
	pthread_exit(0);
}