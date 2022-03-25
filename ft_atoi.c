/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarteau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:59:34 by cmarteau          #+#    #+#             */
/*   Updated: 2022/03/21 03:07:44 by cmarteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	res;
	unsigned int	i;
	unsigned int	k;

	res = 0;
	i = 0;
	k = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == 45 && str[i + 1] != 43)
	{
		k = -1;
		i++;
	}
	if (str[i] == 43)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * k);
}

int	ft_error(int ac, char **av)
{
	int	nb;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	while (--ac > 0)
	{
		if (ft_check_args(av[ac]) == 1)
			return (0);
	}
	nb = ft_atoi(av[1]);
	if (nb == 1)
	{
		printf("%s 0 1 died\n", KMAG);
		return (0);
	}
	if (nb > 200)
	{
		printf("Too many philos for this program\n");
		return (0);
	}
	return (1);
}

int	ft_check_args(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("Invalid parameter\n");
			return (1);
		}
		i++;
	}
	if (i > 10)
		return (1);
	return (0);
}

void	init_phi(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb)
	{
		data->phi[i].nb = data->nb;
		data->phi[i].id = i;
		data->phi[i].stop = 0;
		data->phi[i].time_to_die = data->time_to_die;
		data->phi[i].time_to_eat = data->time_to_eat;
		data->phi[i].time_to_sleep = data->time_to_sleep;
		data->phi[i].meals = data->meals;
		data->phi[i].start = timestamp();
		data->phi[i].data = data;
		pthread_mutex_init(&data->fork[i], NULL);
	}
}

void	print(t_phi *phi, int i)
{
	check_status(phi);
	if (check_death(phi) == 1)
		return ;
	pthread_mutex_lock(&phi->data->print);
	if (i == 1)
		printf("%s%ld %d has taken a fork\n", KRED, \
				timestamp() - phi->data->start, phi->id + 1);
	else if (i == 2)
		printf("%s%ld %d is eating\n", KGRN, \
				timestamp() - phi->data->start, phi->id + 1);
	else if (i == 3)
		printf("%s%ld %d is sleeping\n", KYEL, \
				timestamp() - phi->data->start, phi->id + 1);
	else if (i == 4)
		printf("%s%ld %d is thinking\n", KBLU, \
				timestamp() - phi->data->start, phi->id + 1);
	pthread_mutex_unlock(&phi->data->print);
}
