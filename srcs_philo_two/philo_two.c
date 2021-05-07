/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:45:55 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 02:31:18 by ragegodthor      ###   ########.fr       */
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
		if (sem_wait(philo->die))
			break ;
		interval = get_time(philo->starting_t_d);
		if (interval > philo->time_to_die)
		{
			sem_wait(philo->print);
			interval = get_time(philo->starting_t_p);
			printf("\033[1;31m%ld %d died\n", interval, philo->nbr + 1);
			sem_post(philo->main);
			break ;
		}
		if (sem_post(philo->die))
			break ;
		usleep(3000);
	}
	return (NULL);
}

int		ft_eating(t_philo *philo)
{
	if (sem_wait(philo->fork))
		return (0);
	print_msg(philo, 1, philo->nbr);
	if (sem_wait(philo->fork))
		return (0);
	print_msg(philo, 1, philo->nbr);
	if (sem_wait(philo->die))
		return (0);
	print_msg(philo, 2, philo->nbr);
	if (sem_post(philo->die))
		return (0);
	usleep(philo->time_to_eat * 1000);
	return (1);
}

void	*routine(void *philosopher)
{
	t_philo *philo;

	philo = (t_philo *)philosopher;
	pthread_create(&philo->die_p, NULL, &ft_die, (void *)philo);
	pthread_detach(philo->die_p);
	while (1)
	{
		if (!ft_eating(philo))
			break ;
		if (reaching_nbr_of_eating(philo))
			break ;
		if (sem_post(philo->fork))
			break ;
		if (sem_post(philo->fork))
			break ;
		if (philo->if_true == 1 && \
			philo->number_of_eating == philo->number_time_must_eat)
			break ;
		print_msg(philo, 3, philo->nbr);
		usleep(philo->time_to_sleep * 1000);
		print_msg(philo, 4, philo->nbr);
		usleep(40);
	}
	return (NULL);
}

void	starting_threads(t_philo *philo, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < philo->nb_of_philo)
	{
		pthread_create(&thread[i], NULL, &routine, (void *)&philo[i]);
		pthread_detach(thread[i]);
		usleep(100);
		i++;
	}
}

int		main(int ac, char **av)
{
	t_philo			*philo;
	pthread_t		*thread;
	t_sem			semaphore;
	struct timeval	starting_t;
	int				i;

	check_arguments(ac, av);
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
	free_philo(philo, thread, &semaphore);
	return (0);
}
