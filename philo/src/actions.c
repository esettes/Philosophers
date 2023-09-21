/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:16:58 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/21 23:31:48 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_triggers(t_philo *p, size_t eat, size_t think, size_t sleep)
{
	p->eat = eat;
	p->think = think;
	p->sleep = sleep;
}

void	p_think(t_philo *ph)
{
	print_status(ph->id, ph->data, THINK, RESET_);
	ph->think = 1;
}

void	p_sleep(t_philo *ph)
{
	if (ph->sleep == 0 && ph->eat == 1)
	{
		f_usleep(ph->data->t_to_sleep);
		print_status(ph->id, ph->data, SLEEP, CYAN_);
		set_triggers(ph, 0, 0, 1);
	}
}

void	p_eat(t_data *d, int id, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	if (d->philos[id]->think == 0)
		p_think(d->philos[id]);
	while (1)
	{
		if (pthread_mutex_lock(fork1) == 0 && pthread_mutex_lock(fork2) == 0)
		{
			print_status(id, d, FORK, YELLOW_);
			pthread_mutex_lock(d->mut_eat);
			d->philos[id]->start_eating = get_time();
			pthread_mutex_unlock(d->mut_eat);
			d->philos[id]->eat = 1;
			print_status(id, d, EAT, VIOLET_);
			f_usleep(d->t_to_eat);
			pthread_mutex_unlock(fork1);
			pthread_mutex_unlock(fork2);
			d->philos[id]->times_eaten++;
			print_status(id, d, "has leaving forks", BLUE_);
			set_triggers(d->philos[id], 1, 1, 0);
			break ;
		}
	}
}
