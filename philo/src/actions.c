/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:09:07 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/18 22:30:41 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *ph)
{
	print_status(ph->id, ph->data, THINK, RESET_);
}

void	p_sleep(t_philo *ph)
{
	print_status(ph->id, ph->data, SLEEP, VIOLET_);
	f_usleep(ph->data->t_to_sleep);
}

void	p_eat(t_philo *ph, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(ph->mut);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(fork1);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(fork2);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	else
	{
		pthread_mutex_lock(fork2);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(fork1);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	ph->start_eating = get_time();// - ph->data->start_time;

	ph->times_eaten++;
	
	print_status(ph->id, ph->data, EAT, BLUE_);
	f_usleep(ph->data->t_to_eat);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(fork2);
		pthread_mutex_unlock(fork1);
	}
	else
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
	}
	pthread_mutex_unlock(ph->mut);
	p_sleep(ph);
	//p_think(ph);
}
