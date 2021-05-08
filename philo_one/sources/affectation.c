/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affectation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:16:35 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 02:28:33 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo	*allocation(int ac, char **av, pthread_t **thread)
{
	int		number;
	t_philo	*philo;

	number = ft_atoi(av[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * number);
	affectation(ac, av, &philo);
	*thread = (pthread_t *)malloc(sizeof(pthread_t) * number);
	philo->each_one = (int *)malloc(sizeof(int));
	philo->each_one[0] = 0;
	philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	philo->die = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * number);
	philo->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->block = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->increment = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->main = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	return (philo);
}

void	affectation(int ac, char **av, t_philo **philo)
{
	int	number;
	int	i;

	i = 0;
	number = ft_atoi(av[1]);
	while (i < number)
	{
		(*philo)[i].number_of_eating = 0;
		(*philo)[i].if_true = 0;
		(*philo)[i].reaching = 0;
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

t_philo	*initialisation_mutex(t_philo *philo, int number)
{
	int	i;

	i = 1;
	pthread_mutex_init(philo->print, NULL);
	pthread_mutex_init(philo->block, NULL);
	pthread_mutex_init(philo->main, NULL);
	pthread_mutex_init(philo->increment, NULL);
	while (i < number)
	{
		philo[i].fork = philo->fork;
		philo[i].die = philo->die;
		philo[i].print = philo->print;
		philo[i].block = philo->block;
		philo[i].increment = philo->increment;
		philo[i].main = philo->main;
		if (philo->if_true == 1)
			philo[i].each_one = philo->each_one;
		i++;
	}
	return (philo);
}
