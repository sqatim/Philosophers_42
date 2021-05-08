/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 01:22:21 by ragegodthor       #+#    #+#             */
/*   Updated: 2021/05/08 02:14:57 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_error(int error)
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
	exit(1);
}

int	print_msg(t_philo *philo, int number, int x)
{
	struct timeval	current_t;
	long			interval;

	if (!check_mutex(philo, philo->print, philo->print, 1))
		return (0);
	gettimeofday(&current_t, NULL);
	interval = get_time(philo->starting_t_p);
	if (number == 1)
		printf("\033[1;33m%ld %d has taken a fork\n", interval, x + 1);
	else if (number == 2)
	{
		philo->starting_t_d = \
			current_t.tv_sec * 1000 + current_t.tv_usec / 1000;
		printf("\033[1;32m%ld %d is eating\n", interval, x + 1);
	}
	else if (number == 3)
		printf("\033[1;36m%ld %d is sleeping\n", interval, x + 1);
	else if (number == 4)
		printf("\033[0m%ld %d is thinking\n", interval, x + 1);
	if (!check_mutex(philo, philo->print, philo->print, 2))
		return (0);
	return (1);
}

void	check_arguments(int ac, char **av)
{
	int	index;

	index = 1;
	if (ac < 5 || ac > 6)
	{
		printf("error\n");
		exit(1);
	}
	else
	{
		while (av[index])
		{
			if (!check_number(av[index]))
				print_error(index);
			index++;
		}
	}
}