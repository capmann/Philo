#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nb;
}               t_philo;

typedef struct  s_phi
{
    int             lo_name;
    pthread_mutex_t lock;
    t_philo         philo;
}               t_phi;

int	ft_atoi(const char *str);

long int    timestamp();

t_philo init_philo(char **av);

void    *philo_routine(void *args);

#endif