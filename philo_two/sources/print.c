/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:35:51 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 15:01:41 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	print_error(int error)
{
	char	*str;

	if (error == 1)
		str = "Error in : Number of philosopher\n";
	else if (error == 2)
		str = "Error in : Time to die\n";
	else if (error == 3)
		str = "Error in : Time to eat\n";
	else if (error == 4)
		str = "Error in : Time to sleep\n";
	else
		str = "Error in : Number of time each philosophers must eat\n";
	printf("%s", str);
	return (0);
}

int	check_arguments(int ac, char **av)
{
	int	index;

	index = 1;
	if (ac < 5 || ac > 6)
	{
		printf("error\n");
		return (0);
	}
	else
	{
		while (av[index])
		{
			if (!check_number(av[index]))
				return (print_error(index));
			index++;
		}
	}
	return (1);
}

int	print_msg(t_philo *philo, int number, int nbr)
{
	struct timeval	current_t;
	long			interval;

	if (!check_semaphore(philo, philo->print, 1))
		return (0);
	gettimeofday(&current_t, NULL);
	interval = get_time(philo->starting_t_p);
	if (number == 1)
		printf("\033[1;33m%ld %d has taken a fork\n", interval, nbr + 1);
	else if (number == 2)
	{
		philo->starting_t_d = \
			current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
		printf("\033[1;32m%ld %d is eating\n", interval, nbr + 1);
	}
	else if (number == 3)
		printf("\033[1;36m%ld %d is sleeping\n", interval, nbr + 1);
	else if (number == 4)
		printf("\033[0m%ld %d is thinking\n", interval, nbr + 1);
	if (!check_semaphore(philo, philo->print, 2))
		return (0);
	return (1);
}
