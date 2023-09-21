/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 18:05:12 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_think(t_philo *ph)
{

		//ph->start_thinking = get_time();
		print_status(ph, "is thinking", RESET_);
		//ph->sleep = 0;
}

void	p_sleep(t_philo *ph)
{
	if (ph->sleep == 0 && ph->eat == 1)
	{
		ph->start_sleeping = get_time();
		f_usleep(ph->t_to_sleep);
		print_status(ph, "is sleeping", CYAN_);
		ph->sleep = 1;
		ph->eat = 0;
		ph->think = 0;
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
			print_status(ph, "has taken a fork", YELLOW_);
			ph->r_fork = 1;
		}
		if (pthread_mutex_lock(ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]) == 0)// && ph->r_fork == 1)
		{
			print_status(ph, "has taken a fork", YELLOW_);
			ph->l_fork = 1;
		}
		if (ph->r_fork == 1 && ph->l_fork == 1)
		{
			
			pthread_mutex_lock(ph->mut_eat);
			ph->start_eating = get_time();
			pthread_mutex_unlock(ph->mut_eat);



			ph->eat = 1;
			f_usleep(ph->t_to_eat);
			// when philo finish eat or when starts?
			print_status(ph, "is eating", VIOLET_);
			ph->times_eaten++;
			
			//ph->finish_eat = get_time();
			
			pthread_mutex_unlock(ph->data->forks[ph->id]);
			pthread_mutex_unlock(ph->data->forks[(ph->id + 1)
				% ph->data->num_philos]);
			ph->r_fork = 0;
			ph->l_fork = 0;
			print_status(ph, "has leaving forks", BLUE_);
			ph->think = 1;
			ph->sleep = 0;
			break ;
		}
		// if (ph->think == 0)
		// 	p_think(ph);
	}
}
