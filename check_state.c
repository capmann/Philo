#include "philo.h"

void	check_state(t_phi *phi)
{
	if (phi->nb % 2 == 1)
	{
		if (phi->time_to_die / 3 < phi->time_to_eat
			&& phi->time_to_die > (phi->time_to_eat + phi->time_to_sleep))
			usleep((phi->time_to_die - phi->time_to_eat \
						- phi->time_to_sleep) * 1000);
		else if (phi->id % 2 == 0)
			usleep(100);
	}
	else
	{
		if (phi->time_to_die / 2 < phi->time_to_eat
			&& phi->time_to_die > (phi->time_to_eat + phi->time_to_sleep))
			usleep((phi->time_to_die - phi->time_to_eat \
						- phi->time_to_sleep) * 1000);
	}
}
