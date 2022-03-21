#include "philo.h"

void	*philo_routine(void *args)
{
	t_phi	*phi;
	int		left;
	int		right;

	phi = (t_phi *)args;
	left = phi->id;
	right = phi->id + 1;
	if (phi->id + 1 == phi->nb)
		right = 0;
	if ((phi->id + 1) % 2 == 0)
		usleep(1000);
	while (check_death(phi) == 0 && check_meals(phi) == 0)
	{
		philo_take_forks(phi, left, right);
		philo_eat(phi, left, right);
		philo_sleep(phi);
	}
	return (NULL);
}

void	*check_status(void *args)
{
	t_phi	 *phi;

	phi = (t_phi *)args;
	while (check_death(phi) == 0)
	{
		usleep(100);
		pthread_mutex_lock(&phi->data->death);
		if ((timestamp() - phi->start >= phi->time_to_die \
					&& phi->data->is_dead == 0))
		{
			pthread_mutex_lock(&phi->data->print);
			printf("%s %ld %d died\n", KMAG, timestamp() \
					- phi->data->start, phi->id + 1);
			pthread_mutex_unlock(&phi->data->print);
			phi->data->is_dead = 1;
			phi->stop = 1;
			pthread_mutex_unlock(&phi->data->death);
			break ;
		}
		pthread_mutex_unlock(&phi->data->death);
	}
	return (NULL);
}

long int	timestamp(void)
{
	struct timeval	tv;
	long int		time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

void	init_data(char **av, t_data *data)
{
	data->start = timestamp();
	data->is_dead = 0;
	data->nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->meals = ft_atoi(av[5]);
	else
		data->meals = -1;
	init_phi(data);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
}

int	main(int ac, char **av)
{
	t_data		 d;
	int			 i;

	d = (t_data){};
	i = -1;
	if (ft_error(ac, av) == 0)
		return (0);
	init_data(av, &d);
	while (++i < d.nb)
	{
		pthread_create(&d.phi[i].thread_id, NULL, philo_routine, &d.phi[i]);
		pthread_create(&d.phi[i].thread_death, NULL, check_status, &d.phi[i]);
		usleep(100);
	}
	i = -1;
	while (++i < d.nb)
	{
		pthread_join(d.phi[i].thread_id, NULL);
		pthread_detach(d.phi[i].thread_death);
	}
	i = -1;
	while (++i < d.nb)
		pthread_mutex_destroy(&d.fork[i]);
	pthread_mutex_destroy(&d.print);
	return (0);
}
