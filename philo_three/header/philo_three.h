/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:41:25 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/07 16:54:51 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define FORK_S "/fork"
# define PRINT_S "/print"
# define DIE_S "/die"
# define MAIN_S "/main"
# define EACH_S "/each"
# define EAT_S "/eat"

typedef struct s_philosopher
{
	int			nbr;
	int			nb_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			if_true;
	int			number_time_must_eat;
	long		starting_t_d;
	long		starting_t_p;
	long		current_t;
	int			number_of_eating;
	int			reaching;
	pid_t			pid;
	int			*each_one;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*main;
	sem_t		*die;
	sem_t		*each;
	sem_t		*eat;
	pthread_t	die_p;
}				t_philo;

typedef struct s_semaphore
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*main;
	sem_t	*die;
	sem_t	*each;
	sem_t	*eat;
}				t_sem;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
void			free_philo(t_philo *philo);
void			affectation(int ac, char **av, t_philo **philo);
t_sem			initialisation_semaphore(int number, int ac, int reaching);
int				check_number(char *str);
t_philo			*get_args(int ac, char **av, t_sem *semaphore);
long			get_time(long starting_t);
void			*ft_reaching(void *philosopher);
void			print_error(int error);
void			print_msg(t_philo *philo, int number, int nbr);
void			check_arguments(int ac, char **av);

#endif
