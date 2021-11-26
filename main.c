#include "philo.h"

void    *philo_routine(void *args)
{
    t_phi           *phi;

    phi = (t_phi *)args; 
    pthread_mutex_lock(&phi->lock);
    printf("%ld %d has taken a fork\n", timestamp(), phi->lo_name);
    printf("%ld %d is eating\n", timestamp(), phi->lo_name);
    usleep(phi->philo.time_to_eat * 1000);
    pthread_mutex_unlock(&phi->lock);
    printf("%ld %d is sleeping\n", timestamp(), phi->lo_name);
    usleep(phi->philo.time_to_sleep * 1000);
    printf("%ld %d is thinking\n", timestamp(), phi->lo_name);
    printf("%ld %d died\n", timestamp(), phi->lo_name);
    return NULL;
}

long int    timestamp()
{
    struct timeval  tv;
    long int        time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (time_in_ms);
}

t_philo init_philo(char **av)
{
    t_philo philo;

    philo.nb = ft_atoi(av[1]);
    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep = ft_atoi(av[4]);
    return (philo);
}

int main(int ac, char **av)
{
    t_philo         philo;
    t_phi           phi;
    pthread_t       id[2];
    pthread_mutex_t mutex;

    philo = (t_philo){};
    phi = (t_phi){};
    if (ac != 5)
    {
        write(1, "oh no...\n", 8);
        exit(0);
    }
    philo = init_philo(av);
    pthread_mutex_init(&mutex, NULL);
    while (42)
    {
        while (philo.nb > 0)
        {
            phi.lo_name = philo.nb;
            pthread_create(&id[phi.lo_name], NULL, philo_routine, &phi);
            pthread_join(id[phi.lo_name], NULL);
            philo.nb--;
        }
//        pthread_mutex_destroy(&mutex);
    }
    return (0);
}