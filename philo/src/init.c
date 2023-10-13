/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:21:43 by iostancu          #+#    #+#             */
/*   Updated: 2023/10/13 23:51:05 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data **data, int philos, u_int64_t sleep, u_int64_t eat,
		u_int64_t die, int times_to_eat)
{
	int	i;

	i = 0;
	(*data) = malloc(sizeof(t_data));
	if (!*data)
	{
		ft_putendlc_fd(RED_, ALLOC_ERR, 1);
		return (EXIT_FAILURE);
	}
	(*data)->num_philos = philos;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * ((*data)->num_philos));
	if (!(*data)->forks)
	{
		ft_putendlc_fd(RED_, ALLOC_ERR, 1);
		return (EXIT_FAILURE);
	}
	while (i < (*data)->num_philos)
	{
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
		{
			ft_putendlc_fd(RED_, "Forks init error", 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	(*data)->end_routine = 0;
	(*data)->t_to_die = die;
	(*data)->t_to_eat = eat;
	(*data)->t_to_sleep = sleep;
	(*data)->many_times_to_eat = times_to_eat;
	return (EXIT_SUCCESS);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * (data->num_philos));
	if (!data->philos)
	{
		ft_putendlc_fd(RED_, ALLOC_ERR, 1);
		return (EXIT_FAILURE);
	}
	while (i < data->num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].times_eaten = 0;
		data->philos[i].start_eating = 0;
		data->philos[i].is_die = 0;
		data->philos[i].mut = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->philos[i].mut, NULL);
		pthread_mutex_init(&data->philos[i].m_eat, NULL);
		data->philos[i].tid = malloc(sizeof(pthread_t));
		if (!data->philos[i].tid)
		{
			ft_putendlc_fd(RED_, ALLOC_ERR, 1);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

