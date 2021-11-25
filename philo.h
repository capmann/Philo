#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}               t_philo;

int	ft_atoi(const char *str);

t_philo init_philo(char **av);

#endif