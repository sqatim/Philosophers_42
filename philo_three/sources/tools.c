/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:36:57 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 06:01:20 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

t_philo	*get_args(int ac, char **av, t_sem *semaphore)
{
	t_philo	*philo;
	int		number;
	int		i;

	number = ft_atoi(av[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * number);
	affectation(ac, av, &philo);
	philo->each_one = (int *)malloc(sizeof(int));
	philo->each_one[0] = 0;
	*semaphore = initialisation_semaphore(number, \
			ac, philo->number_time_must_eat);
	i = 0;
	while (i < number)
	{
		philo[i].fork = semaphore->fork;
		philo[i].print = semaphore->print;
		philo[i].main = semaphore->main;
		philo[i].eat = semaphore->eat;
		philo[i].increment = semaphore->increment;
		philo[i].block = semaphore->block;
		sem_unlink(DIE_S);
		philo[i].die = sem_open(DIE_S, O_CREAT, 0777, 1);
		if (ac == 6 && i != 0)
			philo[i].each_one = philo->each_one;
		i++;
	}
	return (philo);
}

long	get_time(long starting_t)
{
	struct timeval	current_t;
	long			current;

	gettimeofday(&current_t, NULL);
	current = (current_t.tv_sec * 1000 + current_t.tv_usec / 1000);
	return (current - starting_t);
}

void	*ft_reaching(void *philosopher)
{
	int		k;
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	k = 0;
	while (1)
	{
		if (!check_semaphore(philo, philo->eat, 1))
			break ;
		if (philo->if_true == 1 && \
			k < philo->nb_of_philo * philo->number_time_must_eat)
		{
			k++;
			if (k == philo->nb_of_philo * philo->number_time_must_eat)
			{
				exit_reach(philo);
				break ;
			}
		}
	}
	return (NULL);
}
