/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 01:46:51 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 02:41:44 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	exit_reach(t_philo *philo)
{
	if (!check_mutex(philo, philo->block, philo->block, 1))
		return (0);
	if (!check_mutex(philo, philo->print, philo->print, 1))
		return (0);
	printf("\033[0m==> Done \U0001F600 \U0001F600\n");
	if (!check_mutex(philo, philo->main, philo->main, 2))
		return (0);
	return (1);
}

void	exit_die(t_philo *philo)
{
	long	interval;

	if (philo->reaching)
		return ;
	if (!check_mutex(philo, philo->block, philo->block, 1))
		return ;
	if (!check_mutex(philo, philo->print, philo->print, 1))
		return ;
	interval = get_time(philo->starting_t_p);
	printf("\033[1;31m%ld %d died\033[0m\n", interval, philo->l + 1);
	if (!check_mutex(philo, philo->main, philo->main, 2))
		return ;
}

int	check_mutex(t_philo *philo, pthread_mutex_t *which, \
			pthread_mutex_t *mutex, int nbr)
{
	if (nbr == 1)
	{
		if (!philo || !which || pthread_mutex_lock(mutex))
			return (0);
	}
	else if (nbr == 2)
	{
		if (!philo || !which || pthread_mutex_unlock(mutex))
			return (0);
	}
	return (1);
}

int	puts_forks(t_philo *philo)
{
	if (!check_mutex(philo, philo->fork, &philo->fork[philo->r], 2))
		return (0);
	if (!check_mutex(philo, philo->fork, &philo->fork[philo->l], 2))
		return (0);
	if (philo->if_true == 1 && \
		philo->number_of_eating == philo->number_time_must_eat)
		return (0);
	return (1);
}
