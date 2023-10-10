#include "philo.h"

int	f_error(char *str, t_data *data)
{
	(void)data;
	(void)str;
	if (data)
		ft_exit(&data);
	return (1);
}

u_int64_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL))
		return (f_error("Error: gettimeofday", NULL));
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
	size_t	end;

	pthread_mutex_lock(&data->mut_end);
	end = data->end_routine;
	pthread_mutex_unlock(&data->mut_end);
	if (end == 1)
		return ;
	pthread_mutex_lock(&data->mut_write);
	p_id = ft_itoa(id);
	time_ = ft_itoa(get_time() - data->start_time);
	ft_putstrc_fd(col, time_, 1);
	free(time_);
	ft_putstrc_fd(col, " ", 1);
	ft_putstrc_fd(col, p_id, 1);
	free(p_id);
	ft_putstrc_fd(col, " ", 1);
	ft_putendlc_fd(col, act, 1);
	pthread_mutex_unlock(&data->mut_write);
}

void	ft_freedata(t_data *data)
{
	free (data);
}

void	*ft_exit(t_data **data)
{
	// int	i;

	// i = 0;
	
	
	// i = 0;
	// while (++i < (*data)->num_philos)
	// {
	// 	if (&(*data)->forks[i])
	// 		pthread_mutex_destroy((*data)->forks[i]);
	// }
	// pthread_mutex_destroy((*data)->mut_write);
	//pthread_mutex_destroy((*data)->mut_eat);
	//if ((*data)->forks)
	//	free ((*data)->forks);
	//if ((*data)->mut_write)
	//	free((*data)->mut_write);
	//if ((*data)->mut_eat)
	//	free((*data)->mut_eat);

	/*while (i <= data->num_philos)
	{
		free(data->philos[i]);
		i++;
	}*/
	//free((*data)->philos);
	(void)data;
	
	return (EXIT_SUCCESS);
}

