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

u_int64_t	get_time_in_ms(u_int64_t start_time)
{
	struct timeval	curr_time;
	u_int64_t		ret;

	if (gettimeofday(&curr_time, NULL))
		return (f_error("gettimeofday() FAILURE\n", NULL));
	ret = (curr_time.tv_sec - start_time) * 1000;
	ret += curr_time.tv_usec / 1000;
	
	return (ret);
}

int	f_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_status(t_philo *p, u_int64_t t, char *act, char *col)
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
