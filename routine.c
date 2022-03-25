#include "philo.h"

void	philo_take_forks(t_phi *phi, int left, int right)
{
	check_status(phi);
	if ((phi->id + 1) % 2 != 0)
	{	
		pthread_mutex_lock(&phi->data->fork[left]);
		print(phi, 1);
		pthread_mutex_lock(&phi->data->fork[right]);
		print(phi, 1);
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(&phi->data->fork[right]);
		print(phi, 1);
		pthread_mutex_lock(&phi->data->fork[left]);
		print(phi, 1);
	}
	phi->start = timestamp();
}

void	philo_eat(t_phi *phi, int left, int right)
{
	check_status(phi);
	if (check_death(phi) == 1 || check_meals(phi) == 1)
	{
		pthread_mutex_unlock(&phi->data->fork[right]);
		pthread_mutex_unlock(&phi->data->fork[left]);
		return ;
	}
	print(phi, 2);
	phi->meals--;
	if (check_death(phi) == 0 && check_meals(phi) == 0)
		usleep(phi->time_to_eat * 1000);
	if ((phi->id + 1) % 2 != 0)
	{
		pthread_mutex_unlock(&phi->data->fork[left]);
		pthread_mutex_unlock(&phi->data->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&phi->data->fork[right]);
		pthread_mutex_unlock(&phi->data->fork[left]);
	}
}

void	philo_sleep(t_phi *phi)
{
	check_state(phi);
	print(phi, 3);
	if (check_death(phi) == 0 && check_meals(phi) == 0)
		usleep(phi->time_to_sleep * 1000);
	print(phi, 4);
	if (phi->time_to_sleep < phi->time_to_eat)
		usleep((phi->time_to_eat - phi->time_to_sleep + 5) * 1000);
}

int	check_meals(t_phi *phi)
{
	int	i;

	i = -1;
	while (++i < phi->nb)
	{
		if (phi->meals != 0)
			return (0);
	}
	return (1);
}

int	check_death(t_phi *phi)
{
	pthread_mutex_lock(&phi->data->death);
	if (phi->data->is_dead == 1)
	{
		pthread_mutex_unlock(&phi->data->death);
		return (1);
	}
	pthread_mutex_unlock(&phi->data->death);
	return (0);
}
