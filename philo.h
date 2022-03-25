#ifndef PHILO_H
# define PHILO_H

# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KGRN "\x1B[32m"
# define KYEL "\x1B[33m"
# define KBLU "\x1B[34m"
# define KMAG "\x1B[35m"
# define KCYN "\x1B[36m"
# define KWHT "\x1B[37m"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_phi
{
	pthread_t	thread_id;
	pthread_t	thread_death;
	t_data		*data;
	int			id;
	int			meals;
	int			nb;
	int			stop;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	long int	start;
}				t_phi;

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	int				nb;
	int				is_dead;
	long int		start;
	pthread_mutex_t	fork[300];
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_phi			phi[300];
}				t_data;

int			ft_atoi(const char *str);
int			check_death(t_phi *phi);
int			check_meals(t_phi *phi);
int			ft_error(int ac, char **av);
int			ft_check_args(char *arg);
long int	timestamp(void);
void		init_data(char **av, t_data *data);
void		init_phi(t_data *data);
void		*check_status(void *args);
void		philo_take_forks(t_phi *phi, int left, int right);
void		philo_eat(t_phi *phi, int left, int right);
void		philo_sleep(t_phi *phi);
void		print(t_phi *phi, int i);
void		*philo_routine(void *args);
void		check_state(t_phi *phi);

#endif
