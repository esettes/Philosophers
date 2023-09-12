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
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (f_error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	f_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void	print_time_and_id_actions(char *time_, char *id, char *action)
{
	ft_putstrc_fd(BLUE_, time_, 1);
	//ft_putstrc_fd(BLUE_, " [", 1);
	ft_putstrc_fd(GREEN_, id, 1);
	ft_putendlc_fd(BLUE_, action, 1);
}

void	print_status(t_philo *philo)
{
	char	*time_;
	char	*p_id;
	char	*str;

	time_ = ft_itoa(get_time()) - philo->start_time;
	p_id = ft_itoa(philo->id);
	print_time_and_id_actions(time_, p_id, " has taken a fork");
	time_ = ft_itoa(get_time()) - philo->start_eating;
	print_time_and_id_actions(time_, p_id, " is eating");
	time_ = ft_itoa(get_time()) - philo->start_sleeping;
	print_time_and_id_actions(time_, p_id, " is sleeping");
	time_ = ft_itoa(get_time()) ;
	print_time_and_id_actions(time_, p_id, " is thinking");
	time_ = ft_itoa(get_time());
	print_time_and_id_actions(time_, p_id, " died");
	free(p_id);
	free(time_);
}