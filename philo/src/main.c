/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 23:46:30 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/02 21:59:33 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*work_philo(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *)philo;

	while (ph->is_die == 0)
	{
		p_eat(ph);
		p_think(ph);
	}
	return ((void *)0);
}

static int	all_philos_eats_many_times(t_philo *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (p[i].times_eaten >= p[i].data->many_times_to_eat)
		{
			p[i].is_die = 1;
			pthread_detach(*p[i].tid);
		}
		else
			return (0);
		i++;
	}
	return (1);
}

void	*exit_checker(void *data)
{
	t_data		*d;
	int			i;
	u_int64_t	curr_time;
	u_int64_t	aux;

	d = (t_data *)data;
	while (1)
	{
		i = 0;
		
		while (i < d->num_philos)
		{
			if (d->t_to_die < d->t_to_eat)
			{
				pthread_mutex_unlock(d->forks[d->philos[i]->id]);
				pthread_mutex_unlock(d->forks[(d->philos[i]->id + 1)
					% d->num_philos]);
				d->philos[i]->is_die = 1;
				break ;
			}
			if (all_philos_eats_many_times(*d->philos, d->num_philos) == 1)
			{
				d->philos[i]->is_die = 1;
				break ;
			}
			curr_time = get_time() - d->start_time;
			pthread_mutex_lock(d->mut_eat);
			aux = d->philos[i]->start_eating;
			pthread_mutex_unlock(d->mut_eat);
			if ((curr_time) > (d->philos[i]->start_eating + d->t_to_die))
			{
				print_status(d->philos[i]->id, d, "died for many time for last eat", RED_);
				d->philos[i]->is_die = 1;
				break ;
			}
			i++;
		}
		if (d->philos[i]->is_die == 1)
			break ;
	}
	print_status(d->philos[i]->id, d, DIE, RED_);
	ft_exit(d);
	return ((void *)0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc <= 1 || argc > 6)
	{
		ft_putstrc_fd(YELLOW_, "./philo [num_of_philosophers] [time_to_sleep] [time_to_eat] ", 1);
		ft_putendlc_fd(YELLOW_, "[time_to_die] opc[many_times_to_eat]", 1);
		exit(EXIT_SUCCESS);
	}
	if (init_data(&data, ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
		 ft_atoi(argv[4]), ft_atoi(argv[5])) != 0)
		ft_exit(data);
	if (init_philos(data) != 0)
		ft_exit(data);
	data->start_time = get_time();
	while (i <= data->num_philos)
	{
		pthread_mutex_init(data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(data->mut_write, NULL);
	pthread_mutex_init(data->mut_eat, NULL);
	pthread_create(&data->controller, NULL, exit_checker, (void *)data);
	for (int i = 0; i < data->num_philos ; i++)
		pthread_create(data->philos[i]->tid, NULL, work_philo, (void *)data->philos[i]);
	ft_exit(data);
}

