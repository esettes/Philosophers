/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:09:07 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 23:55:08 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_sleep(t_philo *ph)
{
	print_status(ph->id, ph->data, SLEEP, CYAN_);
	f_usleep(ph->data->t_to_sleep);
}

int	p_eat(t_philo *ph)
{
	size_t	end;

	end = 0;
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(&ph->data->forks[ph->id]);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	else
	{
		pthread_mutex_lock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(&ph->data->forks[ph->id]);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	pthread_mutex_lock(&ph->m_eat);
	ph->start_eating = get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(&ph->m_eat);
	print_status(ph->id, ph->data, EAT, VIOLET_);
	f_usleep(ph->data->t_to_eat);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		pthread_mutex_unlock(&ph->data->forks[ph->id]);
	}
	else
	{
		pthread_mutex_unlock(&ph->data->forks[ph->id]);
		pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
	}

	/*
	pthread_mutex_lock(&ph->data->forks[ph->id]);
	print_status(ph->id, ph->data, FORK, YELLOW_);
	pthread_mutex_lock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
	print_status(ph->id, ph->data, FORK, YELLOW_);
	
	pthread_mutex_lock(ph->mut);
	ph->start_eating = get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(ph->mut);
	
	print_status(ph->id, ph->data, EAT, VIOLET_);
	f_usleep(ph->data->t_to_eat);
	
	pthread_mutex_unlock(&ph->data->forks[ph->id]);
	pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
	*/
	
	pthread_mutex_lock(&ph->data->mut);
	end = ph->data->end_routine;
	pthread_mutex_unlock(&ph->data->mut);
	if (end == 1 )
		return (1);
	
	p_sleep(ph);
	return (0);
}
