/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:11:44 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/16 19:36:56 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_work(void *philo);
void		*controller_work(void *data);
int			init_program(t_data **data, int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = -1;
	if (init_program(&data, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else
	{
		init_mutexes(data);
		while (++i < data->num_philos)
			pthread_create(data->philos[i].tid, NULL, philo_work,
				&data->philos[i]);
		data->start_time = get_time();
		pthread_create(&data->controller, NULL, controller_work, (void *)data);
		pthread_mutex_unlock(&data->mut_start);
		i = -1;
		while (++i < data->num_philos)
			pthread_join(*data->philos[i].tid, NULL);
		pthread_join(data->controller, NULL);
		pthread_mutex_destroy(&data->mut_write);
		pthread_mutex_destroy(&data->mut_start);
		pthread_mutex_destroy(&data->mut);
		ft_exit(&data, 1);
	}
	return (EXIT_SUCCESS);
}

void	*philo_work(void *philo)
{
	t_philo		*ph;
	size_t		die;

	ph = (t_philo *)philo;
	die = 0;
	pthread_mutex_lock(&ph->data->mut_start);
	pthread_mutex_unlock(&ph->data->mut_start);
	while (die == 0)
	{
		pthread_mutex_lock(&ph->data->mut_write);
		die = ph->is_die;
		pthread_mutex_unlock(&ph->data->mut_write);
		p_eat(ph, &ph->data->forks[ph->id], &ph->data->forks[(ph->id + 1)
			% ph->data->num_philos]);
		print_status(ph->id, ph->data, THINK, RESET_);
	}
	return ((void *)0);
}

static int	is_any_philo_died(t_data *d, size_t *end, int i)
{
	uint64_t	curr_time;
	uint64_t	start_eat;

	if (d->times_to_eat != 0 && all_philos_eats_many_times
		(d->philos, (uint64_t)d->num_philos, d->times_to_eat) == 1)
	{
		finish_routine(d, end, d->philos[i].id);
		return (1);
	}
	pthread_mutex_lock(d->philos[i].mut);
	start_eat = d->philos[i].start_eating;
	pthread_mutex_unlock(d->philos[i].mut);
	curr_time = get_time();
	if ((curr_time - start_eat) > d->t_to_die)
	{
		finish_routine(d, end, d->philos[i].id);
		return (1);
	}
	return (0);
}

void	*controller_work(void *data)
{
	int		i;
	t_data	*d;
	size_t	end;

	d = (t_data *)data;
	i = 0;
	end = 0;
	while (end == 0)
	{
		i = -1;
		while (++i < d->num_philos)
		{
			if (is_any_philo_died(d, &end, i) == 1)
				return ((void *)0);
		}
	}
	return ((void *)0);
}
