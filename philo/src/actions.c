/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/25 22:33:18 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_triggers(t_philo **p, size_t eat, size_t think, size_t sleep)
{
	(*p)->eat = eat;
	(*p)->think = think;
	(*p)->sleep = sleep;
}

void	p_think(t_philo *ph)
{
	print_status(ph->id, ph->data, THINK, RESET_);
	ph->think = 1;
}

void	p_sleep(t_philo *ph)
{
	// if (ph->sleep == 0 && ph->eat == 1)
	// {
		print_status(ph->id, ph->data, SLEEP, CYAN_);
		f_usleep(ph->data->t_to_sleep);
		
		set_triggers(&ph, 0, 0, 1);
	//}
}

void	p_eat(t_philo *ph)//, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	
	while (1)
	{
		if (pthread_mutex_lock(ph->data->forks[ph->id]) == 0)
		{
			ph->r_fork = 1;
			print_status(ph->id, ph->data, " has taken a fork", YELLOW_);
		}
		if (pthread_mutex_lock(ph->data->forks[(ph->id + 1) % ph->data->num_philos]) == 0)
		{
			ph->l_fork = 1;
			print_status(ph->id, ph->data, " has taken a fork", YELLOW_);
		}
		if (ph->r_fork == 1 && ph->l_fork == 1)
		{
			//print_status(id, d, FORK, YELLOW_);
			pthread_mutex_lock(ph->data->mut_eat);
			ph->start_eating = get_time();
			pthread_mutex_unlock(ph->data->mut_eat);
			ph->eat = 1;
			print_status(ph->id, ph->data, EAT, VIOLET_);
			f_usleep(ph->data->t_to_eat);
			pthread_mutex_unlock(ph->data->forks[ph->id]);
			pthread_mutex_unlock(ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
			ph->r_fork = 0;
			ph->l_fork = 0;
			ph->times_eaten++;
			
			print_status(ph->id, ph->data, "has leaving forks", BLUE_);
			p_sleep(ph);
			set_triggers(&ph, 1, 1, 0);
			break ;
		}
	}
}
