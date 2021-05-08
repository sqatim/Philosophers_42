/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 04:09:50 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 04:35:32 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
    {
        sem_post(philo->die);
		return ;
    }
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
