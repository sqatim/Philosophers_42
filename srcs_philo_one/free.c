/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragegodthor <ragegodthor@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:03:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 02:29:33 by ragegodthor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	free_philo(t_philo *philo, pthread_t *thread)
{
	free(philo->fork);
	if(philo->if_true == 1)
		free(philo->each_one);
	free(philo->test_die_m);
	free(philo->mutex);
	free(philo->main);
	free(philo);
	free(thread);
}
