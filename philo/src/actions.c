/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/27 21:54:21 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *ph)
{
	print_status(ph->id, ph->data, THINK, RESET_);
}

void	p_sleep(t_philo *ph)
{
	print_status(ph->id, ph->data, SLEEP, CYAN_);
	f_usleep(ph->data->t_to_sleep);
}
static void	take_forks(t_philo *ph, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	// if (ph->id % 2 == 0)
	// {
	// 	if (pthread_mutex_lock(fork2) == 0)
	// 	{
	// 		ph->l_fork = 1;
	// 		print_status(ph->id, ph->data, FORK, YELLOW_);
	// 	}
	// 	if (pthread_mutex_lock(fork1) == 0 && ph->l_fork == 1)
	// 	{
	// 		ph->r_fork = 1;
	// 		print_status(ph->id, ph->data, FORK, YELLOW_);
	// 	}
	// }
	// else
	// {
	// 	if (pthread_mutex_lock(fork1) == 0)
	// 	{
	// 		ph->r_fork = 1;
	// 		print_status(ph->id, ph->data, FORK, YELLOW_);
	// 	}
	// 	if (pthread_mutex_lock(fork2) == 0 && ph->r_fork == 1)
	// 	{
	// 		ph->l_fork = 1;
	// 		print_status(ph->id, ph->data, FORK, YELLOW_);
	// 	}
	// }
	if (ph->id % 2 == 0)
	{
		f_usleep(10);
		if (pthread_mutex_lock(fork1) == 0)
		{
			ph->r_fork = 1;
			print_status(ph->id, ph->data, FORK, YELLOW_);
		}
		if (pthread_mutex_lock(fork2) == 0 && ph->r_fork == 1)
		{
			ph->l_fork = 1;
			print_status(ph->id, ph->data, FORK, YELLOW_);
		}
	}
	else
	{
		if (pthread_mutex_lock(fork1) == 0)
		{
			ph->r_fork = 1;
			print_status(ph->id, ph->data, FORK, YELLOW_);
		}
		if (pthread_mutex_lock(fork2) == 0 && ph->r_fork == 1)
		{
			ph->l_fork = 1;
			print_status(ph->id, ph->data, FORK, YELLOW_);
		}
	}
}
void	p_eat(t_philo *ph)
{
	while (1)
	{
		take_forks(ph, ph->data->forks[ph->id], ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		if (ph->r_fork == 1 && ph->l_fork == 1)
		{
			pthread_mutex_lock(ph->data->mut_eat);
			ph->start_eating = get_time();
			pthread_mutex_unlock(ph->data->mut_eat);
			print_status(ph->id, ph->data, EAT, VIOLET_);
			f_usleep(ph->data->t_to_eat);
			pthread_mutex_unlock(ph->data->forks[ph->id]);
			pthread_mutex_unlock(ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
			ph->r_fork = 0;
			ph->l_fork = 0;
			ph->times_eaten++;
			p_sleep(ph);
			break ;
		}
	}
}
