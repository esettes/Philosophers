/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:21:43 by iostancu          #+#    #+#             */
/*   Updated: 2023/11/20 21:42:24 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data(t_data **data, char *argv[]);
static int	init_philos(t_data *data);

int	init_program(t_data **data, int argc, char *argv[])
{
	if (is_correct_input(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(data, argv) == EXIT_FAILURE)
	{
		ft_exit(data, 0);
		return (EXIT_FAILURE);
	}
	if (init_philos(*data) == EXIT_FAILURE)
	{
		ft_exit(data, 0);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	init_mutexes(t_data *data)
{
	pthread_mutex_init(&data->mut_write, NULL);
	pthread_mutex_init(&data->mut, NULL);
	pthread_mutex_init(&data->mut_start, NULL);
	pthread_mutex_lock(&data->mut_start);
}

static int	init_data(t_data **data, char *argv[])
{
	int	i;

	i = -1;
	(*data) = malloc(sizeof(t_data));
	(*data)->num_philos = ft_atoi(argv[1]);
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * ((*data)->num_philos));
	(*data)->eat_forks = malloc(sizeof(size_t) * ((*data)->num_philos));
	if (!*data || !(*data)->forks || !(*data)->eat_forks)
		return (EXIT_FAILURE);
	while (++i < (*data)->num_philos)
	{
		(*data)->eat_forks[i] = 0;
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
			return (EXIT_FAILURE);
	}
	(*data)->end_routine = 0;
	(*data)->t_to_die = ft_atoi(argv[2]);
	(*data)->t_to_eat = ft_atoi(argv[3]);
	(*data)->t_to_sleep = ft_atoi(argv[4]);
	(*data)->times_to_eat = ft_atoi(argv[5]);
	return (EXIT_SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * (data->num_philos));
	if (!data->philos)
		return (EXIT_FAILURE);
	while (++i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].times_eaten = 0;
		data->philos[i].start_eating = get_time();
		data->philos[i].is_die = 0;
		data->philos[i].mut = malloc(sizeof(pthread_mutex_t));
		data->philos[i].tid = malloc(sizeof(pthread_t));
		data->philos[i].r_fork = 0;
		data->philos[i].l_fork = 0;
		if (!data->philos[i].mut || !data->philos[i].tid)
			return (EXIT_FAILURE);
		pthread_mutex_init(data->philos[i].mut, NULL);
	}
	if (data->t_to_die < 0 || data->t_to_eat < 0 || data->t_to_sleep < 0
		|| data->times_to_eat < 0 || data->num_philos <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
