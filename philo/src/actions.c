/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/10 23:55:54 by iostancu         ###   ########.fr       */
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
	
	// while (ph->l_fork == 0 || ph->r_fork == 0)
	// {
		if (ph->id % 2 == 0)
		{
			//f_usleep(10);
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
			if (pthread_mutex_lock(fork2) == 0)
			{
				ph->l_fork = 1;
				print_status(ph->id, ph->data, FORK, YELLOW_);
			}
			if (pthread_mutex_lock(fork1) == 0 && ph->l_fork == 1)
			{
				ph->r_fork = 1;
				print_status(ph->id, ph->data, FORK, YELLOW_);
			}
		}
	//}
	
}
void	p_eat(t_philo *ph)
{
	// size_t	end;
	// size_t	die;

	// end = 0;
	// die = 0;
	while (1)
	{
		// pthread_mutex_lock(&ph->data->mut_end);
		// end = ph->data->end_routine;
		// die = ph->is_die;
		// pthread_mutex_unlock(&ph->data->mut_end);
		// if (die == 1 || end == 1)
		// 	break ;
		//if (get_mutex_val(&ph->data->mut_write, ph->data->end_routine) == 1)
		// if (end == 1)
		// {
		// 	//pthread_mutex_unlock(&ph->data->forks[ph->id]);
		// 	//pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		// 	print_status(ph->id, ph->data, " hello !!", GREEN_);
		// 	break ;
		// }
		take_forks(ph, &ph->data->forks[ph->id], &ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
		if (ph->r_fork == 1 && ph->l_fork == 1)
		{
			pthread_mutex_lock(&ph->data->mut_eat);
			ph->start_eating = get_time();
			ph->times_eaten++;
			pthread_mutex_unlock(&ph->data->mut_eat);
			print_status(ph->id, ph->data, EAT, VIOLET_);
			f_usleep(ph->data->t_to_eat);
			pthread_mutex_unlock(&ph->data->forks[ph->id]);
			pthread_mutex_unlock(&ph->data->forks[(ph->id + 1) % ph->data->num_philos]);
			ph->r_fork = 0;
			ph->l_fork = 0;
			//set_mutex_val(&ph->data->mut_write, &ph->times_eaten, ph->times_eaten + 1);
			p_sleep(ph);
			//p_think(ph);
			break ;
		}
	}
}

