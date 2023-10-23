/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:09:07 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/23 22:31:23 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2);
static void	leave_forks(pthread_mutex_t *f1, pthread_mutex_t *f2);
void		p_sleep(t_philo *ph);

void	p_eat(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	take_forks(ph, f1, f2);
	pthread_mutex_lock(ph->mut);
	ph->start_eating = get_time();
	ph->times_eaten++;
	pthread_mutex_unlock(ph->mut);
	print_status(ph->id, ph->data, EAT, BLUE_);
	f_usleep(ph->data->t_to_eat);
	leave_forks(f1, f2);
	p_sleep(ph);
}

void	p_think(t_philo *ph)
{
	print_status(ph->id, ph->data, THINK, RESET_);
}

void	p_sleep(t_philo *ph)
{
	print_status(ph->id, ph->data, SLEEP, VIOLET_);
	f_usleep(ph->data->t_to_sleep);
}

static void	take_forks(t_philo *ph, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	if (ph->id % 2 != 0)
		usleep(50);
	pthread_mutex_lock(f1);
	print_status(ph->id, ph->data, FORK, YELLOW_);
	pthread_mutex_lock(f2);
	print_status(ph->id, ph->data, FORK, YELLOW_);
}

static void	leave_forks(pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_unlock(f1);
	pthread_mutex_unlock(f2);
}
