/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:41:25 by sqatim            #+#    #+#             */
/*   Updated: 2021/05/08 14:58:53 by sqatim           ###   ########.fr       */
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
# define BLOCK_S "/block"
# define INCREMENT_S "/increment"

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
	pid_t		pid;
	int			*each_one;
	sem_t		*fork;
	sem_t		*print;
	sem_t		*main;
	sem_t		*die;
	sem_t		*each;
	sem_t		*eat;
	sem_t		*increment;
	sem_t		*block;
	pthread_t	die_p;
}				t_philo;

typedef struct s_semaphore
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*main;
	sem_t	*increment;
	sem_t	*block;
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
int				print_error(int error);
int				print_msg(t_philo *philo, int number, int nbr);
int				check_arguments(int ac, char **av);
int				check_semaphore(t_philo *philo, sem_t *semaphore, int nbr);
int				puts_forks(t_philo *philo);
void			exit_die(t_philo *philo);
int				exit_reach(t_philo *philo);
int				reaching_nbr_of_eating(t_philo *philo);
void			affectation_semaphore(t_philo **philo, t_sem *semaphore, \
				int number);

#endif
