#include "philo.h"

int	f_error(char *str, t_data *data)
{
	(void)data;
	if (data)
		ft_exit(data);
	return (1);
}

u_int64_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL))
		return (f_error("gettimeofday() FAILURE\n", NULL));
	return ((curr_time.tv_sec * (u_int64_t)1000) + (curr_time.tv_usec / 1000));
}

int	f_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(int id, t_data *data, char *act, char *col)
{
	char	*time_;
	char	*p_id;
	pthread_mutex_lock(data->mut_write);
	p_id = ft_itoa(id);
	time_ = ft_itoa(get_time() - data->start_time);
	ft_putstrc_fd(col, time_, 1);
	ft_putstrc_fd(col, " ", 1);
	ft_putstrc_fd(col, p_id, 1);
	ft_putstrc_fd(col, " ", 1);
	ft_putendlc_fd(col, act, 1);
	if (time_)
		free(time_);
	if (p_id)
		free(p_id);
	pthread_mutex_unlock(data->mut_write);
}

void	*ft_exit(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->controller, NULL);
	while (i < data->num_philos)
	{
		if (*data->philos[i]->tid)
			pthread_detach(*data->philos[i]->tid);
		i++;
	}
	i = 0;
	while (++i < data->num_philos)
	{
		if (&data->forks[i])
			pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(data->mut_write);
	pthread_mutex_destroy(data->mut_eat);
	if (data->forks)
		free (data->forks);
	if (data->mut_write)
		free(data->mut_write);
	if (data->mut_eat)
		free(data->mut_eat);
	i = 0;
	/*while (i <= data->num_philos)
	{
		free(data->philos[i]);
		i++;
	}*/
	/*free(data->philos); */
	free(data);
	exit (EXIT_SUCCESS);
}

