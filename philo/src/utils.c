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

void	print_status(t_philo *p, char *act, char *col)
{
	char	*time_;
	char	*p_id;
	// if (!time_ || !id || !action)
	// 	return ;
	pthread_mutex_lock(p->data->mut_write);
	p_id = ft_itoa(p->id);
	time_ = ft_itoa(get_time() - p->data->start_time);// - t);
	ft_putstrc_fd(col, time_, 1);
	ft_putstrc_fd(col, "ms [", 1);
	ft_putstrc_fd(col, p_id, 1);
	ft_putstrc_fd(col, "] ", 1);
	ft_putendlc_fd(col, act, 1);
	if (time_)
		free(time_);
	if (p_id)
		free(p_id);
	pthread_mutex_unlock(p->data->mut_write);
}

// void	print_status(t_philo *philo)
// {
// 	char	*time_;
// 	char	*p_id;

// 	pthread_mutex_lock(philo->data->mut_write);
// 	time_ = ft_itoa(get_time() - philo->data->epoch_time);
// 	p_id = ft_itoa(philo->id);
// 	print_time_and_id_actions(time_, p_id, " has taken a fork", BLUE_);
// 	time_ = ft_itoa( get_time() - philo->start_eating);// - philo->start_eating;
// 	print_time_and_id_actions(time_, p_id, " is eating", VIOLET_);
// 	// time_ = ft_itoa(get_time()) - philo->start_sleeping;
// 	// print_time_and_id_actions(time_, p_id, " is sleeping");
// 	// time_ = ft_itoa(get_time()) ;
// 	// print_time_and_id_actions(time_, p_id, " is thinking");
// 	// time_ = ft_itoa(get_time());
// 	// print_time_and_id_actions(time_, p_id, " died");
// 	pthread_mutex_unlock(philo->data->mut_write);
// 	if (time_)
// 		free(time_);
// 	if (p_id)
// 		free(p_id);
// }

// void	*philo_log(void *philo)
// {

// }

void	*ft_exit(t_data *data)
{
	int	i;

	i = 0;
	for (int i = 0; i < data->num_philos ; i++)
		pthread_join(*data->philos[i]->tid, NULL);
	
	for (int i = 0; i < data->num_philos ; i++)
		pthread_join(data->philos[i]->log, NULL);

	pthread_join(data->exit_, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->mut_write);
	ft_putendlc_fd(GREEN_, "Finish program", 1);
	i = 1;
	while (i <= data->num_philos)
	{
		free(data->philos[i]->tid);
		i++;
	}
	i = 0;
	// while (data->philos[i])
	// {
	// 	free(data->philos[i]);
	// 	i++;
	// }
	if (data->philos)
		free(data->philos);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(data->philos[i]->mut_eat);
		i++;
	}
	i = 0;
	while (data->forks)
	{
		free(data->forks[i]);
		i++;
	}
	if (data->forks)
		free (data->forks);
	if (data->mut_write)
		free(data->mut_write);
	free(data);
	exit (EXIT_SUCCESS);
}
