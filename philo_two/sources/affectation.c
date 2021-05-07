/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affectation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:33:07 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/07 16:29:41 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		(*philo)[i].nbr = i;
		if (ac == 6)
		{
			(*philo)[i].if_true = 1;
			(*philo)[i].number_time_must_eat = ft_atoi(av[5]);
		}
		i++;
	}
}

t_sem	initialisation_semaphore(int number)
{
	t_sem	semaphore;

	sem_unlink(FORK_S);
	sem_unlink(PRINT_S);
	sem_unlink(DIE_S);
	sem_unlink(MAIN_S);
	semaphore.fork = sem_open(FORK_S, O_CREAT, 0777, number);
	semaphore.print = sem_open(PRINT_S, O_CREAT, 0777, 1);
	semaphore.main = sem_open(MAIN_S, O_CREAT, 0777, 1);
	semaphore.die = sem_open(DIE_S, O_CREAT, 0777, 1);
	return (semaphore);
}
