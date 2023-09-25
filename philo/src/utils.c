#include "philo.h"

int	f_error(char *str, t_data *data)
{
	(void)data;
	//printf("%s\n", str);
	// if (data)
	// 	f_exit(data);
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
	// if (!time_ || !id || !action)
	// 	return ;
	pthread_mutex_lock(data->mut_write);
	p_id = ft_itoa(id);
	time_ = ft_itoa(get_time() - data->start_time);// - t);
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
		//pthread_join(*data->philos[i]->tid, NULL);
		if (*data->philos[i]->tid)
			pthread_detach(*data->philos[i]->tid);
		i++;
	}
	//pthread_detach(data->controller);
	// for (int i = 0; i < data->num_philos ; i++)
	// 	pthread_join(data->philos[i]->log, NULL);
	i = 0;
	while (++i < data->num_philos)
	{
		if (data->forks[i])
			pthread_mutex_destroy(data->forks[i]);
	}
	pthread_mutex_destroy(data->mut_write);
	ft_putendlc_fd(GREEN_, "Finish program", 1);
	i = 0;
	while (data->philos[++i]->tid)
		free(data->philos[i]->tid);
	i = 0;
	// while (i < data->num_philos)
	// {
	// 	free(data->print_act[i]);
	// 	i++;
	// }
	// free(data->print_act);
	// while (data->forks[++i])
	// 	free(data->forks[i]);
	if (data->forks)
		free (data->forks);
	if (data->mut_write)
		free(data->mut_write);
	free(data);
	exit (EXIT_SUCCESS);
}
