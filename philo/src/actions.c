/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 22:55:22 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *ph)
{
	print_status(ph, THINK, RESET_);
	ph->think = 1;
}

void	p_sleep(t_philo *ph)
{
	if (ph->sleep == 0 && ph->eat == 1)
	{
		f_usleep(ph->t_to_sleep);
		print_status(ph, SLEEP, CYAN_);
		set_triggers(ph, 0, 0, 1);
	}
}

void	p_eat(t_philo *ph, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	u_int64_t	curr_time;

	curr_time = get_time();
	
	if (ph->think == 0)
		p_think(ph);
	while (1)
	{
		if (pthread_mutex_lock(fork1) == 0 && pthread_mutex_lock(fork2) == 0)
		{
			print_status(ph, FORK, YELLOW_);
			pthread_mutex_lock(ph->data->mut_eat);
			ph->start_eating = get_time();
			pthread_mutex_unlock(ph->data->mut_eat);
			ph->eat = 1;
			print_status(ph, EAT, VIOLET_);
			f_usleep(ph->t_to_eat);
			pthread_mutex_unlock(fork1);
			pthread_mutex_unlock(fork2);
			ph->times_eaten++;
			print_status(ph, "has leaving forks", BLUE_);
			set_triggers(ph, 1, 1, 0);
			break ;
		}
	}
	
}
