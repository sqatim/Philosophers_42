/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:45:55 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 15:01:59 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_die(void *philosopher)
{
	t_philo			*philo;
	long			interval;
	struct timeval	starting_t;

	philo = (t_philo *)philosopher;
	gettimeofday(&starting_t, NULL);
	philo->starting_t_d = philo->starting_t_p;
	while (1)
	{
		if (!check_semaphore(philo, philo->die, 1))
			break ;
		interval = get_time(philo->starting_t_d);
		if (philo->die && interval > philo->time_to_die)
		{
			exit_die(philo);
			break ;
		}
		if (!check_semaphore(philo, philo->die, 2))
			break ;
		usleep(3000);
	}
	return (NULL);
}

int	ft_eating(t_philo *philo)
{
	if (!check_semaphore(philo, philo->fork, 1))
		return (0);
	if (!print_msg(philo, 1, philo->nbr))
		return (0);
	if (!check_semaphore(philo, philo->fork, 1))
		return (0);
	if (!print_msg(philo, 1, philo->nbr))
		return (0);
	if (!check_semaphore(philo, philo->die, 1))
		return (0);
	if (!print_msg(philo, 2, philo->nbr))
		return (0);
	usleep(philo->time_to_eat * 1000);
	if (!check_semaphore(philo, philo->die, 2))
		return (0);
	return (1);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_create(&philo->die_p, NULL, &ft_die, (void *)philo);
	pthread_detach(philo->die_p);
	while (1)
	{
		if (!ft_eating(philo))
			break ;
		if (reaching_nbr_of_eating(philo))
			break ;
		if (!puts_forks(philo))
			break ;
		if (!print_msg(philo, 3, philo->nbr))
			break ;
		usleep(philo->time_to_sleep * 1000);
		if (!print_msg(philo, 4, philo->nbr))
			break ;
		usleep(40);
	}
	return (NULL);
}

void	starting_threads(t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < philo->nb_of_philo)
	{
		pthread_create(&thread[i], NULL, &routine, (void *)&philo[i]);
		pthread_detach(thread[i]);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	pthread_t		*thread;
	t_sem			semaphore;
	struct timeval	starting_t;
	int				i;

	if (!check_arguments(ac, av))
		return (1);
	philo = get_args(ac, av, &thread, &semaphore);
	if (ac == 5 || (ac == 6 && philo->number_time_must_eat != 0))
	{
		i = 0;
		sem_wait(semaphore.main);
		gettimeofday(&starting_t, NULL);
		while (i < philo[0].nb_of_philo)
		{
			philo[i].starting_t_p = \
				starting_t.tv_sec * 1000 + starting_t.tv_usec / 1000;
			i++;
		}
		starting_threads(philo, thread);
		sem_wait(semaphore.main);
	}
	free_philo(philo, thread);
	return (0);
}
