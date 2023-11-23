/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:28:37 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/23 21:15:14 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_routine(t_data *data, size_t *end, int ph_id)
{
	*end = 1;
	pthread_mutex_lock(&data->mut_write);
	data->end_routine = 1;
	pthread_mutex_unlock(&data->mut_write);
	set_all_philos_as_died(data);
	print_die(ph_id, data, DIE, RED_);
	pthread_mutex_unlock(&data->forks[ph_id]);
	pthread_mutex_unlock(&data->forks[(ph_id + 1) % data->num_philos]);
	pthread_mutex_lock(&data->forks[ph_id]);
	data->eat_forks[ph_id] = 0;
	pthread_mutex_unlock(&data->forks[ph_id]);
	pthread_mutex_lock(&data->forks[(ph_id + 1) % data->num_philos]);
	data->eat_forks[(ph_id + 1) % data->num_philos] = 0;
	pthread_mutex_unlock(&data->forks[(ph_id + 1) % data->num_philos]);
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
			free((*data)->philos[i].mut);
		}
		free((*data)->philos[i].tid);
		i++;
	}
	if ((*data)->forks != NULL)
		free((*data)->forks);
	if ((*data)->eat_forks != NULL)
		free((*data)->eat_forks);
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

unsigned long int	get_time(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL))
		return (f_error("Error: gettimeofday", NULL));
	return ((curr_time.tv_sec * (u_int64_t)1000) + (curr_time.tv_usec / 1000));
}

int	f_usleep(t_data *data, unsigned long int time)
{
	unsigned long int	start;
	size_t				end;

	pthread_mutex_lock(&data->mut_write);
	end = data->end_routine;
	pthread_mutex_unlock(&data->mut_write);
	start = get_time();
	while ((get_time() - start) < time)
	{
		if (end != 0)
			return (1);
		usleep(500);
	}
	return (0);
}
