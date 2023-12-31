/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:09:07 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/20 21:38:55 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2);
static void	leave_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2);
static void	take_a_fork(t_philo *ph, int id, pthread_mutex_t *f);
void		p_sleep(t_philo *ph);

void	p_eat(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	take_forks(ph, f1, f2);
	pthread_mutex_lock(ph->mut);
	ph->start_eating = get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(ph->mut);
	print_status(ph->id, ph->data, EAT, BLUE_);
	f_usleep(ph->data, ph->data->t_to_eat);
	leave_forks(ph, f1, f2);
	p_sleep(ph);
}

void	p_sleep(t_philo *ph)
{
	size_t	end;

	pthread_mutex_lock(&ph->data->mut_write);
	end = ph->data->end_routine;
	pthread_mutex_unlock(&ph->data->mut_write);
	print_status(ph->id, ph->data, SLEEP, VIOLET_);
	if (end != 0)
		return ;
	f_usleep(ph->data, ph->data->t_to_sleep);
}

static void	take_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	size_t	end;

	pthread_mutex_lock(&ph->data->mut_write);
	end = ph->data->end_routine;
	pthread_mutex_unlock(&ph->data->mut_write);
	if (end == 1)
		return ;
	if (ph->id % 2 != 0)
	{
		f_usleep(ph->data, 5);
	}
	take_a_fork(ph, ph->id, f1);
	take_a_fork(ph, (ph->id + 1) % ph->data->num_philos, f2);
}

static void	leave_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
	ph->data->eat_forks[ph->id] = 0;
	pthread_mutex_unlock(f1);
	pthread_mutex_lock(f2);
	ph->data->eat_forks[(ph->id + 1) % ph->data->num_philos] = 0;
	pthread_mutex_unlock(f2);
}

static void	take_a_fork(t_philo *ph, int id, pthread_mutex_t *f)
{
	pthread_mutex_lock(f);
	ph->r_fork = ph->data->eat_forks[id];
	pthread_mutex_unlock(f);
	while (ph->r_fork != 0)
	{
		pthread_mutex_lock(f);
		ph->r_fork = ph->data->eat_forks[id];
		pthread_mutex_unlock(f);
	}
	pthread_mutex_lock(f);
	ph->data->eat_forks[id] = 1;
	pthread_mutex_unlock(f);
	print_status(ph->id, ph->data, FORK, YELLOW_);
}
