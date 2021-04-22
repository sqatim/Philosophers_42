/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sqatim <sqatim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:43:16 by sqatim            #+#    #+#             */
/*   Updated: 2021/04/22 17:24:37 by sqatim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void print_error(int error)
{
    char *str;
    if (error == 1)
        str = "Error in : Number of philosopher\n";
    else if (error == 2)
        str = "Error in : Time to die\n";
    else if (error == 3)
        str = "Error in : Time to eat\n";
    else if (error == 4)
        str = "Error in : Time to sleep\n";
    else if (error == 5)
        str = "Error in : Time to sleep\n";
    else if (error == 6)
        str = "Error in : Number of time each philosophers must eat\n";
    printf("%s", str);
    exit(1);
}

int check_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
void check_arguments(int ac, char **av)
{
    int index;

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

t_philosopher get_args(int ac, char **av)
{
    t_philosopher philo;
    
    philo.philo = NULL;
    philo.number_of_philosopher = ft_atoi(av[1]);
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
        philo.number_time_must_eat = ft_atoi(av[5]);
    return(philo);
}

int main(int ac, char **av)
{
    t_philosopher philo;
    check_arguments(ac, av);
    philo = get_args(ac, av);
    print(philo);
    return (0);
}