/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/29 04:19:00 by ragegodthor      ###   ########.fr       */
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

	i = 0;
	data.nb_of_philo = ft_atoi(av[1]);
	// philo.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo.number_of_philosopher);
	// pthread_mutex_init(&mutex, NULL);
	// pthread_mutex_init(&mutex1, NULL);
	// pthread_mutex_init(&mutex2, NULL);
	// pthread_mutex_init(&mutex3, NULL);

	// philo.i = 0;
	data.philo = (t_philo *)malloc(sizeof(t_philo) * data.nb_of_philo);
	// while (i < data.nb_of_philo)
	// {
	// pthread_mutex_init(&data.philo[i].fork, NULL);
	// i++;
	// }
	// philo.state_forks = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
	// philo.state_philo = (int *)malloc(sizeof(int) * philo.number_of_philosopher);
	i = 0;
	// while (i < data.nb_of_philo)
	// {
	// 	data.philo[i].j = 0;
	// 	// data.philo[i].state = HUNGER;
	// 	// data.philo[i].s_fork = EMPTY;
	// 	i++;
	// 	// philo.state_forks[i++] = EMPTY;
	// }
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
	pthread_mutex_t mutex;
	pthread_mutex_t mutex1;

	t_philo *philo;
	static int check;
	int i;
	static pthread_mutex_t *fork;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex1, NULL);
	check = 1;
	philo = (t_philo *)philosopher;
	i = 0;
	pthread_mutex_lock(&mutex);
	usleep(20);
	if (check == 1)
	{
		++check;
		fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->nb_of_philo);
		while (i < philo->nb_of_philo)
		{
			pthread_mutex_init(&fork[i], NULL);
			i++;
		}
		// fork = create_forks(philo->nb_of_philo, &check);
	}
	// printf("adress ==> %p\n", fork);
	// puts("samir");
	pthread_mutex_unlock(&mutex);
	while (1)
	{
		// puts("hii");
		// puts("hi");
		// pthread_mutex_lock(&mutex);
		// usleep(20);
		pthread_mutex_lock(&fork[philo->l]);
		printf("philo %d take the left fork[%d]\n", philo->l, philo->l);
		pthread_mutex_lock(&fork[philo->r]);
		// pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&mutex1);
		printf("philo %d take the right fork[%d]\n", philo->l, philo->r);
		printf("philo %d start eating\n", philo->l);
		pthread_mutex_unlock(&mutex1);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_lock(&mutex1);
		printf("philo %d put forks\n", philo->l);
		pthread_mutex_unlock(&mutex1);
		pthread_mutex_unlock(&fork[philo->l]);
		pthread_mutex_unlock(&fork[philo->r]);
		printf("philo %d start sleeping\n", philo->l);
		usleep(philo->time_to_sleep * 1000);
		printf("philo %d start thinking\n", philo->l);
	}
	i = 0;
	while (i < philo->nb_of_philo)
		pthread_mutex_destroy(&fork[i++]);
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
	// while (i < data.philo->nb_of_philo)
	// {
	// pthread_mutex_init(&data.philo[i].fork, NULL);
	// i++;
	// }
	i = 0;
	while (i < data.nb_of_philo)
	{
		data.philo[i].l = i;
		data.philo[i].r = (i + data.nb_of_philo - 1) % data.nb_of_philo;
		pthread_create(&thread[i], NULL, &routine, (void *)&data.philo[i]);
		usleep(100);
		pthread_detach(thread[i]);
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