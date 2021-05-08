/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:36:57 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 04:55:29 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	get_time(long starting_t)
{
	struct timeval	current_t;
	long			current;

	gettimeofday(&current_t, NULL);
	current = (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	return (current - starting_t);
}

t_philo	*get_args(int ac, char **av, pthread_t **thread, t_sem *semaphore)
{
	t_philo	*philo;
	int		number;
	int		i;

	number = ft_atoi(av[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * number);
	affectation(ac, av, &philo);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * number);
	philo->each_one = (int *)malloc(sizeof(int));
	philo->each_one[0] = 0;
	*semaphore = initialisation_semaphore(number);
	i = 0;
	while (i < number)
	{
		philo[i].fork = semaphore->fork;
		philo[i].print = semaphore->print;
		philo[i].main = semaphore->main;
		philo[i].increment = semaphore->increment;
		philo[i].block = semaphore->block;
		sem_unlink(DIE_S);
		philo[i].die = sem_open(DIE_S, O_CREAT, 0777, 1);
		// printf("adress ==> %p\n",philo[i].die);
		if (philo->if_true == 1 && i != 0)
			philo[i].each_one = philo->each_one;
		i++;
	}
	return (philo);
}

int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	reaching_nbr_of_eating(t_philo *philo)
{
	if (philo->each_one && philo->if_true == 1 && \
		philo->number_of_eating < philo->number_time_must_eat)
	{
		if (!check_semaphore(philo, philo->increment, 1))
			return (0);
		philo->number_of_eating++;
		if((philo->if_true == 1 && \
			philo->number_of_eating == philo->number_time_must_eat))
			philo->reaching = 1;
		philo->each_one[0]++;
		if (philo->each_one[0] == \
			philo->nb_of_philo * philo->number_time_must_eat)
			return (exit_reach(philo));
		if (!check_semaphore(philo, philo->increment, 2))
			return (0);
	}
	return (0);
}
