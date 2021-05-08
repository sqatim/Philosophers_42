/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 05:27:50 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 14:31:31 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	exit_reach(t_philo *philo)
{
	if (!check_semaphore(philo, philo->block, 1))
		return (0);
	if (!check_semaphore(philo, philo->print, 1))
		return (0);
	printf("\033[0m==> Done \U0001F600 \U0001F600\n");
	if (!check_semaphore(philo, philo->main, 2))
		return (0);
	return (1);
}

void	exit_die(t_philo *philo)
{
	long	interval;

	if (philo->reaching)
		return ;
	if (!check_semaphore(philo, philo->block, 1))
		return ;
	if (!check_semaphore(philo, philo->print, 1))
		return ;
	interval = get_time(philo->starting_t_p);
	printf("\033[1;31m%ld %d died\033[0m\n", interval, philo->nbr + 1);
	if (!check_semaphore(philo, philo->main, 2))
		return ;
}

int	check_semaphore(t_philo *philo, sem_t *semaphore, int nbr)
{
	if (nbr == 1)
	{
		if (!philo || !semaphore || sem_wait(semaphore))
			return (0);
	}
	else if (nbr == 2)
	{
		if (!philo || !semaphore || sem_post(semaphore))
			return (0);
	}
	return (1);
}

int	puts_forks(t_philo *philo)
{
	if (!check_semaphore(philo, philo->fork, 2))
		return (0);
	if (!check_semaphore(philo, philo->fork, 2))
		return (0);
	if (philo->if_true == 1 && \
		philo->number_of_eating == philo->number_time_must_eat)
		return (0);
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
		if ((philo->if_true == 1 && \
			philo->number_of_eating == philo->number_time_must_eat))
			philo->reaching = 1;
		if (!check_semaphore(philo, philo->eat, 2))
			return (0);
		if (!check_semaphore(philo, philo->increment, 2))
			return (0);
	}
	return (1);
}
