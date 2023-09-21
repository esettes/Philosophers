/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 21:33:11 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *ph)
{

		//ph->start_thinking = get_time();
		print_status(ph, THINK, RESET_);
		//ph->sleep = 0;
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

void	p_eat(t_philo *ph)
{
	u_int64_t	curr_time;

	curr_time = get_time();
	if (ph->think == 0)
		p_think(ph);
	while (ph->r_fork == 0 && ph->l_fork == 0)
	{
		if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0)
		{
			print_status(ph, FORK, YELLOW_);
			ph->r_fork = 1;
		}
		if (pthread_mutex_lock(ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]) == 0)// && ph->r_fork == 1)
		{
			print_status(ph, FORK, YELLOW_);
			ph->l_fork = 1;
		}
		if (ph->r_fork == 1 && ph->l_fork == 1)
		{
			
			pthread_mutex_lock(ph->mut_eat);
			ph->start_eating = get_time();
			pthread_mutex_unlock(ph->mut_eat);

			ph->eat = 1;
			print_status(ph, EAT, VIOLET_);
			f_usleep(ph->t_to_eat);
			
			ph->times_eaten++;
			pthread_mutex_unlock(ph->data->forks[ph->id]);
			pthread_mutex_unlock(ph->data->forks[(ph->id + 1)
				% ph->data->num_philos]);
			ph->r_fork = 0;
			ph->l_fork = 0;
			print_status(ph, "has leaving forks", BLUE_);
			set_triggers(ph, 1, 1, 0);
			break ;
		}
	}
}
