/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:28:37 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/25 19:48:10 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_routine(t_data *data, size_t *end, int ph_id)
{
	int	i;

	i = 0;
	*end = 1;
	set_all_philos_as_died(data);
	while (i < data->num_philos)
	{
		ft_putstrc_fd(VIOLET_, "philo: ", 1);
		ft_putstrc_fd(VIOLET_, ft_itoa(ph_id), 1);
		ft_putstrc_fd(VIOLET_, " is die: ", 1);
		ft_putendlc_fd(VIOLET_, ft_itoa(data->philos[i].is_die), 1);
		i++;
	}
	ft_putstrc_fd(GREEN_, "philo: ", 1);
	ft_putstrc_fd(GREEN_, ft_itoa(ph_id), 1);
	ft_putendlc_fd(GREEN_, " Finish", 1);
	
	printf("mutex last fork unlock: %i \n", pthread_mutex_unlock(&data->forks[ph_id]));
	printf("mutex last fork unlock: %i \n", pthread_mutex_unlock(&data->forks[(ph_id + 1) % data->num_philos]));
	print_die(ph_id, data, DIE, RED_);
	pthread_mutex_lock(&data->mut_write);
	data->end_routine = 1;
	pthread_mutex_unlock(&data->mut_write);
	
}

void	ft_exit(t_data **data, int mut)
{
	int	i;

	i = 0;
	while (i < (*data)->num_philos)
	{
		if (&(*data)->forks[i] != NULL)
			pthread_mutex_destroy(&(*data)->forks[i]);
		if (mut)
		{
			pthread_mutex_destroy((*data)->philos[i].mut);
			free((*data)->philos[i].tid);
			free((*data)->philos[i].mut);
		}
		i++;
	}
	if ((*data)->forks != NULL)
		free((*data)->forks);
	if ((*data)->philos != NULL)
		free((*data)->philos);
	
	free(*data);
}

int	f_error(char *str, t_data *data)
{
	(void)data;
	(void)str;
	if (data)
		ft_exit(&data, 1);
	return (1);
}

uint64_t	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL))
		return (f_error("Error: gettimeofday", NULL));
	return ((curr_time.tv_sec * (u_int64_t)1000) + (curr_time.tv_usec / 1000));
}

int	f_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(81);
	return (0);
}
