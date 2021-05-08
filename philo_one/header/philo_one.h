/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:40:48 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 14:55:39 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int				r;
	int				l;
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				if_true;
	int				number_time_must_eat;
	long			starting_t_d;
	long			starting_t_p;
	long			current_t;
	long			reaching;
	int				number_of_eating;
	int				*each_one;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*block;
	pthread_mutex_t	*main;
	pthread_mutex_t	*increment;
	pthread_mutex_t	*die;
	pthread_mutex_t	*test_die_m;
	pthread_t		die_p;
}				t_philo;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			free_philo(t_philo **philo, pthread_t *thread);
long			get_time(long starting_t);
t_philo			*get_args(int ac, char **av, pthread_t **thread);
int				check_arguments(int ac, char **av);
t_philo			*allocation(int ac, char **av, pthread_t **thread);
void			affectation(int ac, char **av, t_philo **philo);
t_philo			*initialisation_mutex(t_philo *philo, int number);
int				check_number(char *str);
int				print_error(int error);
int				print_msg(t_philo *philo, int number, int x);
void			starting_threads(t_philo *philo, pthread_t *thread);
int				reaching_nbr_of_eating(t_philo *philo);
int				puts_forks(t_philo *philo);
int				check_mutex(t_philo *philo, pthread_mutex_t *which, \
				pthread_mutex_t *mutex, int nbr);
void			exit_die(t_philo *philo);
int				exit_reach(t_philo *philo);

#endif
