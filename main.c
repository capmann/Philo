#include "philo.h"

t_philo init_philo(char **av)
{
    t_philo philo;

    philo.time_to_die = ft_atoi(av[2]);
    philo.time_to_eat = ft_atoi(av[3]);
    philo.time_to_sleep = ft_atoi(av[4]);
    return (philo);
}

int main(int ac, char **av)
{
    t_philo philo;
    int     nb_philos;

    philo = (t_philo){};
    if (ac != 5)
    {
        write(1, "oh no...\n", 8);
        exit(0);
    }
    philo = init_philo(av);
    while (42)
    {
        nb_philos = ft_atoi(av[1]);
        while (nb_philos > 0)
        {
            printf("%d %d has taken a fork\n", gettimeofday(), nb_philos);
            printf("%d %d is eating\n", gettimeofday(), nb_philos);
            usleep(philo.time_to_eat * 1000);
            printf("%d %d is sleeping\n", gettimeofday(), nb_philos);
            usleep(philo.time_to_sleep * 1000);
            printf("%d %d is thinking\n", gettimeofday(), nb_philos);
            printf("%d %d died\n", gettimeofday(), nb_philos);
            nb_philos--;
        }
    }
    return (0);
}