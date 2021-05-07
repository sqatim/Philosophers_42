/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:36:57 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 17:45:27 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

t_philo	*get_args(int ac, char **av, pthread_t **thread)
{
	t_philo	*philo;
	int		number;
	int		i;

	number = ft_atoi(av[1]);
	philo = allocation(ac, av, &(*thread));
	i = 0;
	while (i < number)
	{
		pthread_mutex_init(&philo->fork[i], NULL);
		pthread_mutex_init(&philo->die[i], NULL);
		i++;
	}
	philo = initialisation_mutex(philo, number);
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
	if (philo->if_true == 1 && \
		philo->number_of_eating < philo->number_time_must_eat)
	{
		philo->number_of_eating++;
		if((philo->if_true == 1 && \
			philo->number_of_eating == philo->number_time_must_eat))
			philo->reaching = 1;
		philo->each_one[0]++;
		if (philo->each_one[0] == \
			philo->nb_of_philo * philo->number_time_must_eat)
		{
			printf("\033[0m==> Done \U0001F600 \U0001F600\n");
			pthread_mutex_unlock(philo->main);
			return (1);
		}
	}
	return (0);
}
