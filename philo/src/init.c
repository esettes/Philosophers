/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 22:06:57 by iostancu          #+#    #+#             */
/*   Updated: 2023/09/14 23:24:17 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data **data, int n_philos, useconds_t t_to_sleep, useconds_t t_to_eat,
		useconds_t t_to_die, useconds_t many_times_to_eat)
{
	(*data) = malloc(sizeof(t_data));
	if (!*data)
	{
		ft_putendlc_fd(RED_, "Data allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->num_philos = n_philos;
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	(*data)->mut = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	//data->philo = NULL;
	if (!(*data)->forks || !(*data)->mut)
	{
		ft_putendlc_fd(RED_, "Data mutexes allocation error", 1);
		return (EXIT_FAILURE);
	}
	(*data)->t_to_die = t_to_die;
	(*data)->t_to_eat = t_to_eat;
	(*data)->t_to_sleep = t_to_sleep;
	(*data)->many_times_to_eat = many_times_to_eat;
	return (EXIT_SUCCESS);
}

int	init_philos(t_data **data)
{
	int	i;
	int	j;

	i = (*data)->num_philos;
	(*data)->philos = malloc(sizeof(t_philo *) * i);
	if (!(*data)->philos)
	{
		ft_putendlc_fd(RED_, "Philosophers allocation error", 1);
		return (EXIT_FAILURE);
	}
	j = i;
	while (i > 0)
	{
		printf("philo id: = %d\n", j);
		(*data)->philos[i]->id = j;
		(*data)->philos[i]->data = *data;
		(*data)->philos[i]->times_eaten = 0;
		(*data)->philos[i]->t_to_die = (*data)->t_to_die;
		(*data)->philos[i]->t_to_eat = (*data)->t_to_eat;
		(*data)->philos[i]->t_to_sleep = (*data)->t_to_sleep;
		(*data)->philos[i]->many_times_to_eat = (*data)->many_times_to_eat;
		(*data)->philos[i]->start_eating = 0;
		(*data)->philos[i]->start_sleeping = 0;
		(*data)->philos[i]->start_thinking = 0;
		(*data)->philos[i]->start_time = 0;
		// (*data)->philos[i].tid = malloc(sizeof(pthread_t));
		// if (!(*data)->philos[i].tid)
		// {
		// 	ft_putendlc_fd(RED_, "Thread allocation error", 1);
		// 	return (EXIT_FAILURE);
		// }
		i--;
		j--;
	}
	return (EXIT_SUCCESS);
}