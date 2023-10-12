/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:09:07 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 00:47:32 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_sleep(t_philo *ph)
{
	print_status(ph->id, ph->data, SLEEP, CYAN_);
	f_usleep(ph->data->t_to_sleep);
}

void	p_eat(t_philo *ph)
{
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(ph->r_fork);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(ph->l_fork);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	else
	{
		pthread_mutex_lock(ph->l_fork);
		print_status(ph->id, ph->data, FORK, YELLOW_);
		pthread_mutex_lock(ph->r_fork);
		print_status(ph->id, ph->data, FORK, YELLOW_);
	}
	pthread_mutex_lock(&ph->mut);
	ph->start_eating = get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(&ph->mut);
	print_status(ph->id, ph->data, EAT, VIOLET_);
	f_usleep(ph->data->t_to_eat);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(ph->l_fork);
		pthread_mutex_unlock(ph->r_fork);
	}
	else
	{
		pthread_mutex_unlock(ph->r_fork);
		pthread_mutex_unlock(ph->l_fork);
	}
	p_sleep(ph);
}
