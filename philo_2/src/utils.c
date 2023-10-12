/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:28:37 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 00:01:37 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->num_philos)
	{
		if (&(*data)->forks[i] != NULL)
			pthread_mutex_destroy(&(*data)->forks[i]);
		//if (&(*data)->philos[i].mut)
		pthread_mutex_destroy(&(*data)->philos[i].mut);
		//free((*data)->philos[i].tid);
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
		ft_exit(&data);
	return (1);
}

uint64_t	get_time(void)
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
